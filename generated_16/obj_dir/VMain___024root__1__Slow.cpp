// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMain.h for the primary calling header

#include "VMain__pch.h"

VL_ATTR_COLD void VMain___024root___ctor_var_reset_0(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___ctor_var_reset_1(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___ctor_var_reset_2(VMain___024root* vlSelf);

VL_ATTR_COLD void VMain___024root___ctor_var_reset(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___ctor_var_reset\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VMain___024root___ctor_var_reset_0(vlSelf);
    VMain___024root___ctor_var_reset_1(vlSelf);
    VMain___024root___ctor_var_reset_2(vlSelf);
}
