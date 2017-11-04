//
// Copyright (c) 2017 Martin Moene
//
// https://github.com/martinmoene/optional-bare
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef NONSTD_OPTIONAL_BARE_HPP
#define NONSTD_OPTIONAL_BARE_HPP

#define optional_bare_VERSION "0.0.0"

#include <cassert>
#include <stdexcept>

namespace nonstd { namespace optional_bare {

// type for nullopt

struct nullopt_t
{
    struct init{};
    nullopt_t( init ) {}
};

// extra parenthesis to prevent the most vexing parse:

const nullopt_t nullopt(( nullopt_t::init() ));

// optional access error.

class bad_optional_access : public std::logic_error
{
public:
  explicit bad_optional_access()
  : logic_error( "bad optional access" ) {}
};

// Simplistic optional: requires T to be default constructible, copyable.

template< typename T >
class optional
{
private:
    typedef void (optional::*safe_bool)() const;

public:
    typedef T value_type;

    optional()
    : has_value_( false )
    {}

    optional( nullopt_t )
    : has_value_( false )
    {}

    optional( T const & arg )
    : has_value_( true )
    , value_    ( arg   )
    {}

    optional & operator=( nullopt_t )
    {
        reset();
        return *this;
    }

    void swap( optional & rhs )
    {
        using std::swap;
        if      ( has_value() == true  && rhs.has_value() == true  ) { swap( **this, *rhs ); }
        else if ( has_value() == false && rhs.has_value() == true  ) { value = *rhs; rhs.reset(); }
        else if ( has_value() == true  && rhs.has_value() == false ) { rhs.value = **this; reset(); }
    }

    // observers

    value_type const * operator->() const
    {
        return assert( has_value() ),
            &value_;
    }

    value_type * operator->()
    {
        return assert( has_value() ),
            &value_;
    }

    value_type const & operator*() const
    {
        return assert( has_value() ),
            value_;
    }

    value_type & operator*()
    {
        return assert( has_value() ),
            value_;
    }

    operator safe_bool() const
    {
        return has_value() ? &optional::this_type_does_not_support_comparisons : 0;
    }

    bool has_value() const
    {
        return has_value_;
    }

    value_type const & value() const
    {
        if ( ! has_value() )
            throw bad_optional_access();

        return value_;
    }

    value_type & value()
    {
        if ( ! has_value() )
            throw bad_optional_access();

        return value_;
    }

    template< class U >
    value_type value_or( U const & v ) const
    {
        return has_value() ? value() : static_cast<value_type>( v );
    }

    // modifiers

    void reset()
    {
        has_value_ = false;
    }

private:
    void this_type_does_not_support_comparisons() const {}

private:
    bool has_value_;
    value_type value_;
};

// Relational operators

template< typename T >
inline bool operator==( optional<T> const & x, optional<T> const & y )
{
    return bool(x) != bool(y) ? false : bool(x) == false ? true : *x == *y;
}

template< typename T >
inline bool operator!=( optional<T> const & x, optional<T> const & y )
{
    return !(x == y);
}

template< typename T >
inline bool operator<( optional<T> const & x, optional<T> const & y )
{
    return (!y) ? false : (!x) ? true : *x < *y;
}

template< typename T >
inline bool operator>( optional<T> const & x, optional<T> const & y )
{
    return (y < x);
}

template< typename T >
inline bool operator<=( optional<T> const & x, optional<T> const & y )
{
    return !(y < x);
}

template< typename T > inline bool operator>=( optional<T> const & x, optional<T> const & y )
{
    return !(x < y);
}

// Comparison with nullopt

template< typename T >
inline bool operator==( optional<T> const & x, nullopt_t )
{
    return (!x);
}

template< typename T >
inline bool operator==( nullopt_t, optional<T> const & x )
{
    return (!x);
}

template< typename T >
inline bool operator!=( optional<T> const & x, nullopt_t )
{
    return bool(x);
}

template< typename T >
inline bool operator!=( nullopt_t, optional<T> const & x )
{
    return bool(x);
}

template< typename T >
inline bool operator<( optional<T> const &, nullopt_t )
{
    return false;
}

template< typename T >
inline bool operator<( nullopt_t, optional<T> const & x )
{
    return bool(x);
}

template< typename T >
inline bool operator<=( optional<T> const & x, nullopt_t )
{
    return (!x);
}

template< typename T >
inline bool operator<=( nullopt_t, optional<T> const & )
{
    return true;
}

template< typename T >
inline bool operator>( optional<T> const & x, nullopt_t )
{
    return bool(x);
}

template< typename T >
inline bool operator>( nullopt_t, optional<T> const & )
{
    return false;
}

template< typename T >
inline bool operator>=( optional<T> const &, nullopt_t )
{
    return true;
}

template< typename T >
inline bool operator>=( nullopt_t, optional<T> const & x )
{
    return (!x);
}

// Comparison with T

template< typename T >
inline bool operator==( optional<T> const & x, const T& v )
{
    return bool(x) ? *x == v : false;
}

template< typename T >
inline bool operator==( T const & v, optional<T> const & x )
{
    return bool(x) ? v == *x : false;
}

template< typename T >
inline bool operator!=( optional<T> const & x, const T& v )
{
    return bool(x) ? *x != v : true;
}

template< typename T >
inline bool operator!=( T const & v, optional<T> const & x )
{
    return bool(x) ? v != *x : true;
}

template< typename T >
inline bool operator<( optional<T> const & x, const T& v )
{
    return bool(x) ? *x < v : true;
}

template< typename T >
inline bool operator<( T const & v, optional<T> const & x )
{
    return bool(x) ? v < *x : false;
}

template< typename T >
inline bool operator<=( optional<T> const & x, const T& v )
{
    return bool(x) ? *x <= v : true;
}

template< typename T >
inline bool operator<=( T const & v, optional<T> const & x )
{
    return bool(x) ? v <= *x : false;
}

template< typename T >
inline bool operator>( optional<T> const & x, const T& v )
{
    return bool(x) ? *x > v : false;
}

template< typename T >
inline bool operator>( T const & v, optional<T> const & x )
{
    return bool(x) ? v > *x : true;
}

template< typename T >
inline bool operator>=( optional<T> const & x, const T& v )
{
    return bool(x) ? *x >= v : false;
}

template< typename T >
inline bool operator>=( T const & v, optional<T> const & x )
{
    return bool(x) ? v >= *x : true;
}

// Specialized algorithms

template< typename T >
void swap( optional<T> & x, optional<T> & y )
{
    x.swap( y );
}

// Convenience function to create an optional.

template< typename T >
inline optional<T> make_optional( T const & v )
{
    return optional<T>( v );
}

} // namespace optional-bare

using namespace optional_bare;

} // namespace nonstd

#endif // NONSTD_OPTIONAL_BARE_HPP
