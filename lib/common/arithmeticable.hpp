#pragma once

#include <addable.hpp>
#include <subtractable.hpp>

template <class Derived>
struct arithmeticable : public addable<Derived>,
                        public subtractable<Derived> {};
