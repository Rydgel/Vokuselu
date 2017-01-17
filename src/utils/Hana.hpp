#ifndef VOXELS_HANA_HPP
#define VOXELS_HANA_HPP

#include <boost/hana.hpp>
#include <boost/variant.hpp>
#include <boost/signals2.hpp>

namespace hana = boost::hana;
namespace signals = boost::signals2;

// My case wrapper
template <class Ret, class Caller>
struct CaseVisitor: boost::static_visitor<Ret> {
    CaseVisitor(const Caller & caller): caller_ { caller } {}

    template <class T>
    auto operator()(const T & t) const { return caller_(t); }

    const Caller & caller_;
};

// Const variant version
template <class T, template <class...> class V, class F, class... Ts, class... Fs>
auto case_(const V<T, Ts...> & variant, F && f, Fs &&... fs) {
    return boost::apply_visitor(
            hana::overload_linearly(f, fs...),
            variant
    );
};

// Hana -> boost::variant helper
constexpr auto make_variant_over = hana::reverse_partial(
        hana::unpack,
        hana::template_<boost::variant>
);

// Argument type deduction helper
template <class F>
struct FirstParameter {
    template <class R, class C, class P1>
    static constexpr auto deduce(R (C::*)(P1) const) {
        return hana::decltype_(hana::type_c<P1>); // Strips const-ref qualifiers
    }

    using type = typename decltype(deduce(&F::operator()))::type;
};

#endif //VOXELS_HANA_HPP
