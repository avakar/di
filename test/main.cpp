#include <avakar/di.h>
#include <mutest/test.h>

using avakar::di;

struct A { int x = 0; };
struct B {};
struct C {};
struct D: C {};

TEST("empty di can be instantiated")
{
	di<> d1;
}

TEST("empty di can be copied")
{
	di<> d1;
	di<> d2 = d1;
}

TEST("di with one dependency")
{
	di<A> d1 = { A{ 1 } };

	chk d1.get<A>().x == 1;
}

TEST("di with multiple dependencies")
{
	D b;

	di<A, C *> deps { &b, A() };
	chk deps.get<C *>() == &b;
}

TEST("di can be sourced from another di")
{
	A a1, a2;
	B b1, b2;
	D d;

	di<A *, B *> d1 = { &a1, &b1 };

	di<A *, B *, C *> d2 = { &d, &a2, d1, &b2 };
	chk d2.get<A *>() == &a2;
	chk d2.get<B *>() == &b1;
	chk d2.get<C *>() == &d;
}
