//
// Copyright 2017 by Martin Moene
//
// This code is licensed under the MIT License (MIT).
//
// optional bare is derived from optional lite. optional lite is inspired on std::optional
// by Fernando Cacciola and  Andrzej Krzemienski and on expected lite by Martin Moene.

#include "optional-bare.t.h"

using nonstd::optional;
using nonstd::nullopt;
using nonstd::bad_optional_access;
using nonstd::make_optional;

namespace {

struct nonpod { nonpod(){} };

// ensure comparison of pointers for lest:

// const void * lest_nullptr = 0;

struct S
{
    S( int v )
    : value( v ) {}
    
    int value;
};

struct NoDefaultCopyMove
{
    std::string text;
    NoDefaultCopyMove( std::string text ) : text( text ) {}

private:
    NoDefaultCopyMove();
    NoDefaultCopyMove( NoDefaultCopyMove const & );
    void operator=   ( NoDefaultCopyMove const & );
};

} // anonymous namespace

//
// test specification:
//

//
// optional member operations:
//

// construction:

CASE( "optional: Allows to default construct an empty optional" )
{
    optional<int> a;

    EXPECT( !a );
}

CASE( "optional: Allows to explicitly construct a disengaged, empty optional via nullopt" )
{
    optional<int> a( nullopt );

    EXPECT( !a );
}

#ifdef optional_bare_CONFIG_CONFIRMS_COMPILATION_ERRORS
CASE( "optional: Disallows to default construct an empty optional with a non-default-constructible (define optional_bare_CONFIG_CONFIRMS_COMPILATION_ERRORS)" )
{
//  FAILS: NoDefaultCopyMove x;
    optional<NoDefaultCopyMove> a;

    EXPECT( !a );
}
#endif

CASE( "optional: Allows to copy-construct from empty optional" )
{
    optional<int> a;

    optional<int> b( a );

    EXPECT( !b );
}

CASE( "optional: Allows to copy-construct from non-empty optional" )
{
    optional<int> a( 7 );

    optional<int> b( a );

    EXPECT(  b      );
    EXPECT( *b == 7 );
}

CASE( "optional: Allows to copy-construct from literal value" )
{
    optional<int> a = 7;

    EXPECT(  a      );
    EXPECT( *a == 7 );
}

CASE( "optional: Allows to copy-construct from value" )
{
    const int i = 7;
    optional<int> a( i );

    EXPECT(  a      );
    EXPECT( *a == 7 );
}

CASE( "optional: Allows to copy-construct from optional with different value type" )
{
    optional<int> a( optional<char>( 7 ) );

    EXPECT(  a      );
    EXPECT( *a == 7 );
}

// assignment:

CASE( "optional: Allows to assign nullopt to disengage" )
{
    optional<int>  a( 7 );

    a = nullopt;

    EXPECT( !a );
}

CASE( "optional: Allows to copy-assign from/to engaged and disengaged optionals" )
{
    SETUP( "" ) {
        optional<int> d1;
        optional<int> d2;
        optional<int> e1( 123 );
        optional<int> e2( 987 );

    SECTION( "a disengaged optional assigned nullopt remains empty" ) {
        d1 = nullopt;
        EXPECT( !d1 );
    }
    SECTION( "a disengaged optional assigned an engaged optional obtains its value" ) {
        d1 = e1;
        EXPECT(  d1 );
        EXPECT( *d1 == 123 );
    }
    SECTION( "an engaged optional assigned an engaged optional obtains its value" ) {
        e1 = e2;
        EXPECT(  e1 );
        EXPECT( *e1 == 987 );
    }
    SECTION( "an engaged optional assigned nullopt becomes empty" ) {
        e1 = nullopt;
        EXPECT( !e1 );
    }
    SECTION( "a disengaged optional assigned a disengaged optional remains empty" ) {
        d1 = d2;
        EXPECT( !d1 );
    }}
}

CASE( "optional: Allows to copy-assign from literal value" )
{
    optional<int> a;

    a = 7;

    EXPECT( *a == 7 );
}

CASE( "optional: Allows to copy-assign from value" )
{
    const int i = 7;
    optional<int> a;

    a = i;

    EXPECT( *a == i );
}

CASE( "optional: Allows to copy-assign from optional with different value type" )
{
    optional<int> a;
    
    a = optional<char>( 7 );

    EXPECT(  a      );
    EXPECT( *a == 7 );
}

// swap:

CASE( "optional: Allows to swap with other optional (member)" )
{
    SETUP( "" ) {
        optional<int> d1;
        optional<int> d2;
        optional<int> e1( 42 );
        optional<int> e2( 7 );

    SECTION( "swap disengaged with disengaged optional" ) {
        d1.swap( d2 );
        EXPECT( !d1 );
    }
    SECTION( "swap engaged with engaged optional" ) {
        e1.swap( e2 );
        EXPECT(  e1  );
        EXPECT(  e2 );
        EXPECT( *e1 == 7 );
        EXPECT( *e2 == 42 );
    }
    SECTION( "swap disengaged with engaged optional" ) {
        d1.swap( e1 );
        EXPECT(  d1 );
        EXPECT( !e1 );
        EXPECT( *d1 == 42 );
    }
    SECTION( "swap engaged with disengaged optional" ) {
        e1.swap( d1 );
        EXPECT(  d1 );
        EXPECT( !e1 );
        EXPECT( *d1 == 42 );
    }}
}

// observers:

struct Integer { int x; Integer(int x) : x(x) {} };

CASE( "optional: Allows to obtain pointer to value via operator->()" )
{
    SETUP( "" ) {
        optional<Integer> e( Integer( 42 ) );

    SECTION( "operator->() yields pointer to value (const)" ) {
        EXPECT(  e->x == 42 );
    }
    SECTION( "operator->() yields pointer to value (non-const)" ) {
        e->x = 7;
        EXPECT(  e->x == 7 );
    }}
}

CASE( "optional: Allows to obtain value via operator*()" )
{
    SETUP( "" ) {
        optional<int> e( 42 );

    SECTION( "operator*() yields value (const)" ) {
        EXPECT( *e == 42 );
    }
    SECTION( "operator*() yields value (non-const)" ) {
        *e = 7;
        EXPECT( *e == 7 );
    }}
}

CASE( "optional: Allows to obtain engaged state via has_value()" )
{
    optional<int> a;
    optional<int> b( 7 );

    EXPECT_NOT( a.has_value() );
    EXPECT(     b.has_value() );
}

CASE( "optional: Allows to obtain has_value() via operator bool()" )
{
    optional<int> a;
    optional<int> b( 7 );

    EXPECT_NOT( a );
    EXPECT(     b );
}

CASE( "optional: Allows to obtain value via value()" )
{
    SETUP( "" ) {
        optional<int> e( 42 );

    SECTION( "value() yields value (const)" ) {
        EXPECT( e.value() == 42 );
    }
    SECTION( "value() yields value (non-const)" ) {
        e.value() = 7;
        EXPECT( e.value() == 7 );
    }}
}

CASE( "optional: Allows to obtain value or default via value_or()" )
{
    SETUP( "" ) {
        optional<int> d;
        optional<int> e( 42 );

    SECTION( "value_or( 7 ) yields value for non-empty optional" ) {
        EXPECT( e.value_or( 7 ) == 42 );
    }
    SECTION( "value_or( 7 ) yields default for empty optional" ) {
        EXPECT( d.value_or( 7 ) == 7 );
    }}
}

CASE( "optional: Throws bad_optional_access at disengaged access" )
{
    EXPECT_THROWS_AS( optional<int>().value(), bad_optional_access );
}

// modifiers:

CASE( "optional: Allows to reset content" )
{
    optional<int> a = 7;

    a.reset();

    EXPECT_NOT( a.has_value() );
}

//
// optional non-member functions:
//

CASE( "optional: Allows to swap engage state and values (non-member)" )
{
    SETUP( "" ) {
        optional<int> d1;
        optional<int> d2;
        optional<int> e1( 42 );
        optional<int> e2( 7 );

    SECTION( "swap disengaged with disengaged optional" ) {
        swap( d1, d2 );
        EXPECT( !d1 );
    }
    SECTION( "swap engaged with engaged optional" ) {
        swap( e1, e2 );
        EXPECT(  e1  );
        EXPECT(  e2 );
        EXPECT( *e1 == 7 );
        EXPECT( *e2 == 42 );
    }
    SECTION( "swap disengaged with engaged optional" ) {
        swap( d1, e1 );
        EXPECT(  d1 );
        EXPECT( !e1 );
        EXPECT( *d1 == 42 );
    }
    SECTION( "swap engaged with disengaged optional" ) {
        swap( e1, d1 );
        EXPECT(  d1 );
        EXPECT( !e1 );
        EXPECT( *d1 == 42 );
    }}
}

CASE( "optional: Provides relational operators" )
{
    SETUP( "" ) {
        optional<int> d;
        optional<int> e1( 6 );
        optional<int> e2( 7 );

    SECTION( "engaged    == engaged"    ) { EXPECT(   e1 == e1  ); }
    SECTION( "engaged    == disengaged" ) { EXPECT( !(e1 == d ) ); }
    SECTION( "disengaged == engaged"    ) { EXPECT( !(d  == e1) ); }

    SECTION( "engaged    != engaged"    ) { EXPECT(   e1 != e2  ); }
    SECTION( "engaged    != disengaged" ) { EXPECT(   e1 != d   ); }
    SECTION( "disengaged != engaged"    ) { EXPECT(   d  != e2  ); }

    SECTION( "engaged    <  engaged"    ) { EXPECT(   e1 <  e2  ); }
    SECTION( "engaged    <  disengaged" ) { EXPECT( !(e1 <  d ) ); }
    SECTION( "disengaged <  engaged"    ) { EXPECT(   d  <  e2  ); }

    SECTION( "engaged    <= engaged"    ) { EXPECT(   e1 <= e1  ); }
    SECTION( "engaged    <= engaged"    ) { EXPECT(   e1 <= e2  ); }
    SECTION( "engaged    <= disengaged" ) { EXPECT( !(e1 <= d ) ); }
    SECTION( "disengaged <= engaged"    ) { EXPECT(   d  <= e2  ); }

    SECTION( "engaged    >  engaged"    ) { EXPECT(   e2 >  e1  ); }
    SECTION( "engaged    >  disengaged" ) { EXPECT(   e2 >  d   ); }
    SECTION( "disengaged >  engaged"    ) { EXPECT( !(d  >  e1) ); }

    SECTION( "engaged    >= engaged"    ) { EXPECT(   e1 >= e1  ); }
    SECTION( "engaged    >= engaged"    ) { EXPECT(   e2 >= e1  ); }
    SECTION( "engaged    >= disengaged" ) { EXPECT(   e2 >= d   ); }
    SECTION( "disengaged >= engaged"    ) { EXPECT( !(d  >= e1) ); }

    SECTION( "disengaged == nullopt"    ) { EXPECT(  (d       == nullopt) ); }
    SECTION( "nullopt    == disengaged" ) { EXPECT(  (nullopt == d      ) ); }
    SECTION( "engaged    == nullopt"    ) { EXPECT(  (e1      != nullopt) ); }
    SECTION( "nullopt    == engaged"    ) { EXPECT(  (nullopt != e1     ) ); }
    SECTION( "disengaged == nullopt"    ) { EXPECT( !(d       <  nullopt) ); }
    SECTION( "nullopt    == disengaged" ) { EXPECT( !(nullopt <  d      ) ); }
    SECTION( "disengaged == nullopt"    ) { EXPECT(  (d       <= nullopt) ); }
    SECTION( "nullopt    == disengaged" ) { EXPECT(  (nullopt <= d      ) ); }
    SECTION( "disengaged == nullopt"    ) { EXPECT( !(d       >  nullopt) ); }
    SECTION( "nullopt    == disengaged" ) { EXPECT( !(nullopt >  d      ) ); }
    SECTION( "disengaged == nullopt"    ) { EXPECT(  (d       >= nullopt) ); }
    SECTION( "nullopt    == disengaged" ) { EXPECT(  (nullopt >= d      ) ); }

    SECTION( "engaged    == value"      ) { EXPECT( e1 == 6  ); }
    SECTION( "value     == engaged"     ) { EXPECT(  6 == e1 ); }
    SECTION( "engaged   != value"       ) { EXPECT( e1 != 7  ); }
    SECTION( "value     != engaged"     ) { EXPECT(  6 != e2 ); }
    SECTION( "engaged   <  value"       ) { EXPECT( e1 <  7  ); }
    SECTION( "value     <  engaged"     ) { EXPECT(  6 <  e2 ); }
    SECTION( "engaged   <= value"       ) { EXPECT( e1 <= 7  ); }
    SECTION( "value     <= engaged"     ) { EXPECT(  6 <= e2 ); }
    SECTION( "engaged   >  value"       ) { EXPECT( e2 >  6  ); }
    SECTION( "value     >  engaged"     ) { EXPECT(  7 >  e1 ); }
    SECTION( "engaged   >= value"       ) { EXPECT( e2 >= 6  ); }
    SECTION( "value     >= engaged"     ) { EXPECT(  7 >= e1 ); }
    }
}

CASE( "make_optional: Allows to copy-construct optional" )
{
    S s( 7 );

    EXPECT( make_optional( s )->value == 7 );
}

//
// Negative tests:
//

//
// Tests that print information:
//

struct Struct{ Struct(){} };

#define optional_OUTPUT_SIZEOF( type ) \
    "sizeof( optional<" #type "> ): " << \
     sizeof( optional<   type>   )    << " (" << sizeof(type) << ")\n" <<

CASE("storage_t: Show sizeof various optionals"
     "[.]" )
{
    std::cout <<
         optional_OUTPUT_SIZEOF( char )
         optional_OUTPUT_SIZEOF( short )
         optional_OUTPUT_SIZEOF( int )
         optional_OUTPUT_SIZEOF( long )
         optional_OUTPUT_SIZEOF( float )
         optional_OUTPUT_SIZEOF( double )
         optional_OUTPUT_SIZEOF( long double )
         optional_OUTPUT_SIZEOF( Struct )
         "";
}
#undef optional_OUTPUT_SIZEOF

//
// Issues:
//

// end of file
