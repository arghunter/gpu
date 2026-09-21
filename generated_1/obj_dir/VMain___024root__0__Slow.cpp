// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMain.h for the primary calling header

#include "VMain__pch.h"

VL_ATTR_COLD void VMain___024root___eval_static(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_static\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
    vlSelfRef.__Vtrigprevexpr___TOP__io_execute__0 
        = vlSelfRef.io_execute;
    vlSelfRef.__Vtrigprevexpr___TOP__io_allocate_warps__0 
        = vlSelfRef.io_allocate_warps;
    vlSelfRef.__Vtrigprevexpr___TOP__io_warp_count__0 
        = vlSelfRef.io_warp_count;
    vlSelfRef.__Vtrigprevexpr___TOP__io_vga_clk__0 
        = vlSelfRef.io_vga_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_req_ready__0 
        = vlSelfRef.io_mem_req_ready;
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[0U] 
        = vlSelfRef.io_mem_resp[0U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[1U] 
        = vlSelfRef.io_mem_resp[1U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[2U] 
        = vlSelfRef.io_mem_resp[2U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[3U] 
        = vlSelfRef.io_mem_resp[3U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[4U] 
        = vlSelfRef.io_mem_resp[4U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[5U] 
        = vlSelfRef.io_mem_resp[5U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[6U] 
        = vlSelfRef.io_mem_resp[6U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[7U] 
        = vlSelfRef.io_mem_resp[7U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[8U] 
        = vlSelfRef.io_mem_resp[8U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[9U] 
        = vlSelfRef.io_mem_resp[9U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[10U] 
        = vlSelfRef.io_mem_resp[10U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[11U] 
        = vlSelfRef.io_mem_resp[11U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[12U] 
        = vlSelfRef.io_mem_resp[12U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[13U] 
        = vlSelfRef.io_mem_resp[13U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[14U] 
        = vlSelfRef.io_mem_resp[14U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_resp__0[15U] 
        = vlSelfRef.io_mem_resp[15U];
    vlSelfRef.__Vtrigprevexpr___TOP__io_mem_valid__0 
        = vlSelfRef.io_mem_valid;
    vlSelfRef.__Vtrigprevexpr___TOP__io_rxd__0 = vlSelfRef.io_rxd;
    vlSelfRef.__Vtrigprevexpr___TOP__clock__1 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__io_vga_clk__1 
        = vlSelfRef.io_vga_clk;
}

VL_ATTR_COLD void VMain___024root___eval_initial(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_initial\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VMain___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);
VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__0(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__1(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__2(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__3(VMain___024root* vlSelf);

VL_ATTR_COLD bool VMain___024root___eval_stl(VMain___024root* vlSelf, CData/*0:0*/ firstIteration) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_stl\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(firstIteration)));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VMain___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = VMain___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        {
            // Inlined CFunc: _eval_body__stl
            if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
                VMain___024root___stl_sequent__TOP__0(vlSelf);
                VMain___024root___stl_sequent__TOP__1(vlSelf);
                VMain___024root___stl_sequent__TOP__2(vlSelf);
                VMain___024root___stl_sequent__TOP__3(vlSelf);
            }
        }
    }
    return (__VstlExecute);
}

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__stl(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__stl\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VMain___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__ico(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__ico\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VMain___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__act(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__act\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VMain___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
}

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__nba(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__nba\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    VMain___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
}

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__obs(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__obs\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VMain___024root___eval_dump_triggers__react(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_dump_triggers__react\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VMain___024root___eval_final(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___eval_final\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VMain___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VMain___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___trigger_anySet__stl\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__0(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___stl_sequent__TOP__0\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__isDivOp 
        = ((4U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__func3)) 
           | (5U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__func3)));
    vlSelfRef.io_hsync = (1U & (~ ((0x028fU < (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__hCount)) 
                                   & (0x02f0U > (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__hCount)))));
    vlSelfRef.io_vsync = (1U & (~ ((0x01e9U < (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__vCount)) 
                                   & (0x01ecU > (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__vCount)))));
    vlSelfRef.io_mem_req_bits_wdata[0U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[0U];
    vlSelfRef.io_mem_req_bits_wdata[1U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[1U];
    vlSelfRef.io_mem_req_bits_wdata[2U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[2U];
    vlSelfRef.io_mem_req_bits_wdata[3U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[3U];
    vlSelfRef.io_mem_req_bits_wdata[4U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[4U];
    vlSelfRef.io_mem_req_bits_wdata[5U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[5U];
    vlSelfRef.io_mem_req_bits_wdata[6U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[6U];
    vlSelfRef.io_mem_req_bits_wdata[7U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[7U];
    vlSelfRef.io_mem_req_bits_wdata[8U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[8U];
    vlSelfRef.io_mem_req_bits_wdata[9U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[9U];
    vlSelfRef.io_mem_req_bits_wdata[10U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[10U];
    vlSelfRef.io_mem_req_bits_wdata[11U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[11U];
    vlSelfRef.io_mem_req_bits_wdata[12U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[12U];
    vlSelfRef.io_mem_req_bits_wdata[13U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[13U];
    vlSelfRef.io_mem_req_bits_wdata[14U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[14U];
    vlSelfRef.io_mem_req_bits_wdata[15U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg[15U];
    vlSelfRef.Main__DOT__core__DOT__decode__DOT__decoder__DOT__format 
        = (((0x37U == (0x0000007fU & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst)) 
            | (0x17U == (0x0000007fU & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst)))
            ? 4U : ((0x13U == (0x0000007fU & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                     ? 1U : (((0x0fU == (0x0000007fU 
                                         & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                               ? 1U : ((0x73U == (0x0000007fU 
                                                  & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                                        ? 2U : ((3U 
                                                 == 
                                                 (0x0000007fU 
                                                  & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                                                 ? 1U
                                                 : 
                                                ((0x23U 
                                                  == 
                                                  (0x0000007fU 
                                                   & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                                                  ? 2U
                                                  : 
                                                 ((0x6fU 
                                                   == 
                                                   (0x0000007fU 
                                                    & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                                                   ? 5U
                                                   : 
                                                  ((0x67U 
                                                    == 
                                                    (0x0000007fU 
                                                     & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))
                                                    ? 1U
                                                    : 
                                                   (3U 
                                                    & (- (IData)(
                                                                 (0x63U 
                                                                  == 
                                                                  (0x0000007fU 
                                                                   & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst))))))))))) 
                             & (- (IData)((0x33U != 
                                           (0x0000007fU 
                                            & vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_inst)))))));
    vlSelfRef.Main__DOT___core_io_dcache_req_write_data 
        = ((vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
            [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][2U] 
            << 0x00000014U) | (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                               [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][1U] 
                               >> 0x0000000cU));
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT___q_q_io_deq_bits_func3 
        = (7U & (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                 [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U] 
                 >> 1U));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___GEN_5 
        = ((0x33U != (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           & (5U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)));
    vlSelfRef.io_complete = ((~ ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_0) 
                                 | ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_1) 
                                    | ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_2) 
                                       | (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_3))))) 
                             & (vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__next_warp 
                                == vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__warp_count));
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT___q_q_io_deq_bits_write 
        = (1U & vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
           [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U]);
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__io_mem_req_valid_0 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__mem_req_accepted)) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__busy));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__read_enable 
        = (1U & ((~ (0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state))) 
                 | (1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8 = (1U 
                                                & ((~ 
                                                    (0U 
                                                     != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))) 
                                                   | (1U 
                                                      == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN 
        = ((((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__lmask_3) 
             << 3U) | ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__lmask_2) 
                       << 2U)) | (((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__lmask_1) 
                                   << 1U) | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__lmask_0)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13 = (1U 
                                                 & ((~ 
                                                     (0U 
                                                      != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state))) 
                                                    | (1U 
                                                       == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16 = ((3U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                                 | (0x23U 
                                                    == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN[0U] 
        = vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_0;
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN[1U] 
        = vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_1;
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN[2U] 
        = (IData)((((QData)((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_3)) 
                    << 0x00000020U) | (QData)((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_2))));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN[3U] 
        = (IData)(((((QData)((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_3)) 
                     << 0x00000020U) | (QData)((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_2))) 
                   >> 0x00000020U));
    vlSelfRef.Main__DOT__vga_controller__DOT__active 
        = ((0x0280U > (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__hCount)) 
           & (0x01e0U > (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__vCount)));
    if (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_en_d0) {
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[0U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][0U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[1U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][1U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[2U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][2U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[3U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][3U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[4U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][4U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[5U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][5U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[6U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][6U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[7U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][7U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[8U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][8U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[9U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][9U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[10U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][10U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[11U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][11U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[12U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][12U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[13U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][13U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[14U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][14U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[15U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0][15U];
    } else {
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[0U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[0U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[1U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[1U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[2U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[2U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[3U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[3U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[4U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[4U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[5U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[5U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[6U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[6U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[7U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[7U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[8U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[8U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[9U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[9U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[10U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[10U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[11U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[11U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[12U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[12U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[13U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[13U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[14U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[14U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data[15U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0[15U];
    }
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN 
        = (vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__next_warp 
           < vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__warp_count);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_14 = ((0x33U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                                 & (0x20U 
                                                    == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)));
    if (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT___R0_en_d0) {
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[0U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][0U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[1U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][1U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[2U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][2U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[3U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][3U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[4U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][4U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[5U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][5U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[6U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][6U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[7U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][7U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[8U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][8U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[9U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][9U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[10U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][10U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[11U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][11U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[12U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][12U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[13U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][13U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[14U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][14U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[15U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory
            [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0][15U];
    } else {
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[0U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[0U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[1U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[1U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[2U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[2U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[3U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[3U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[4U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[4U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[5U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[5U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[6U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[6U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[7U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[7U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[8U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[8U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[9U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[9U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[10U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[10U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[11U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[11U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[12U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[12U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[13U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[13U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[14U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[14U];
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[15U] 
            = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0[15U];
    }
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT__active 
        = ((1U & (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                  [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U] 
                  >> 0x0000000bU)) >> (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__lane));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0 
        = (1U & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__valid)) 
                 | (IData)(vlSelfRef.Main__DOT__core__DOT__execute_io_flush_REG)));
    vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ptr_match 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__deq_ptr_value) 
           == (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__enq_ptr_value));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___pc_plus_imm_T 
        = (vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_immediate 
           + vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_pc);
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT___GEN_1 
        = (1U & ((~ (0U != (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state))) 
                 | (1U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20 = ((4U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                                                 | (5U 
                                                    == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ptr_match 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__deq_ptr_value) 
           == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__enq_ptr_value));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__isM 
        = ((0x33U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           & (1U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)));
    vlSelfRef.Main__DOT___core_io_dcache_req_address 
        = (((vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
             [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][3U] 
             << 0x00000014U) | (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                                [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][2U] 
                                >> 0x0000000cU)) + 
           ((vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
             [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][1U] 
             << 0x00000014U) | (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                                [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U] 
                                >> 0x0000000cU)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___meta_array_ext_R0_data 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT___R0_en_d0)
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT__Memory
           [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT___R0_addr_d0]
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT____Vxrand___0);
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___meta_array_ext_R0_data 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT___R0_en_d0)
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT__Memory
           [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT___R0_addr_d0]
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT____Vxrand___0);
    vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__sel_b)
             ? ((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_en_d0)
                 ? vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory
                [vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_addr_d0]
                 : vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT____Vxrand___0)
             : ((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_en_d0)
                 ? vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory
                [vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_addr_d0]
                 : vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT____Vxrand___0)) 
           & (- (IData)((1U & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__b_x0))))));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_4 
        = ((((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_3) 
             << 3U) | ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_2) 
                       << 2U)) | (((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_1) 
                                   << 1U) | (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_0)));
    vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__sel_a)
             ? ((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R1_en_d0)
                 ? vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory
                [vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R1_addr_d0]
                 : vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT____Vxrand___1)
             : ((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT___R1_en_d0)
                 ? vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory
                [vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT___R1_addr_d0]
                 : vlSelfRef.Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT____Vxrand___1)) 
           & (- (IData)((1U & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__a_x0))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34 = ((4U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
                                                 | (5U 
                                                    == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23 = (((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_2) 
                                                  << 2U) 
                                                 | (((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_1) 
                                                     << 1U) 
                                                    | (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_0)));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[0U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_31) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_30) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_29) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_28))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_27) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_26) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_25) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_24))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_23) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_22) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_21) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_20))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_19) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_18) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_17) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_16))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_15) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_14) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_13) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_12))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_11) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_10) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_9) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_8))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_7) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_6) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_5) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_4))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_3) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_2) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_1) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_0))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[1U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_63) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_62) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_61) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_60))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_59) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_58) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_57) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_56))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_55) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_54) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_53) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_52))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_51) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_50) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_49) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_48))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_47) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_46) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_45) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_44))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_43) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_42) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_41) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_40))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_39) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_38) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_37) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_36))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_35) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_34) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_33) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_32))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[2U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_95) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_94) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_93) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_92))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_91) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_90) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_89) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_88))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_87) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_86) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_85) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_84))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_83) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_82) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_81) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_80))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_79) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_78) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_77) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_76))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_75) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_74) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_73) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_72))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_71) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_70) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_69) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_68))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_67) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_66) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_65) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_64))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[3U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_127) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_126) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_125) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_124))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_123) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_122) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_121) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_120))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_119) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_118) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_117) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_116))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_115) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_114) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_113) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_112))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_111) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_110) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_109) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_108))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_107) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_106) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_105) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_104))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_103) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_102) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_101) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_100))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_99) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_98) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_97) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_96))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[4U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_159) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_158) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_157) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_156))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_155) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_154) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_153) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_152))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_151) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_150) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_149) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_148))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_147) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_146) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_145) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_144))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_143) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_142) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_141) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_140))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_139) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_138) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_137) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_136))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_135) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_134) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_133) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_132))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_131) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_130) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_129) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_128))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[5U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_191) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_190) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_189) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_188))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_187) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_186) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_185) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_184))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_183) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_182) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_181) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_180))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_179) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_178) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_177) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_176))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_175) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_174) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_173) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_172))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_171) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_170) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_169) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_168))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_167) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_166) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_165) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_164))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_163) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_162) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_161) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_160))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[6U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_223) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_222) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_221) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_220))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_219) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_218) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_217) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_216))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_215) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_214) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_213) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_212))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_211) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_210) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_209) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_208))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_207) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_206) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_205) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_204))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_203) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_202) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_201) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_200))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_199) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_198) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_197) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_196))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_195) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_194) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_193) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_192))))));
    vlSelfRef.Main__DOT__memory__DOT___keyTracker_io_keyDown[7U] 
        = (((((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_255) 
                  << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_254) 
                            << 2U)) | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_253) 
                                        << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_252))) 
               << 0x0000000cU) | (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_251) 
                                     << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_250) 
                                               << 2U)) 
                                   | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_249) 
                                       << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_248))) 
                                  << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_247) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_246) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_245) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_244))) 
                                              << 4U) 
                                             | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_243) 
                                                  << 3U) 
                                                 | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_242) 
                                                    << 2U)) 
                                                | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_241) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_240))))) 
            << 0x00000010U) | (((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_239) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_238) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_237) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_236))) 
                                 << 0x0000000cU) | 
                                (((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_235) 
                                    << 3U) | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_234) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_233) 
                                      << 1U) | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_232))) 
                                 << 8U)) | ((((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_231) 
                                                << 3U) 
                                               | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_230) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_229) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_228))) 
                                             << 4U) 
                                            | ((((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_227) 
                                                 << 3U) 
                                                | ((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_226) 
                                                   << 2U)) 
                                               | (((IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_225) 
                                                   << 1U) 
                                                  | (IData)(vlSelfRef.Main__DOT__memory__DOT__keyTracker__DOT__keyState_224))))));
}

VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__1(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___stl_sequent__TOP__1\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ Main__DOT__core__DOT___writeback_io_write_enable;
    Main__DOT__core__DOT___writeback_io_write_enable = 0;
    SData/*9:0*/ Main__DOT__vga_controller__DOT__vCountShifted;
    Main__DOT__vga_controller__DOT__vCountShifted = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_35;
    __VdfgRegularize_h6e95ff9d_0_35 = 0;
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<4>/*127:0*/ __Vtemp_8;
    // Body
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ptr_match 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value) 
           == (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__enq_ptr_value));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___meta_array_ext_R0_data 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT___R0_en_d0)
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT__Memory
           [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0]
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT____Vxrand___0);
    vlSelfRef.io_mem_req_bits_write = (2U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_ack 
        = ((IData)(vlSelfRef.io_mem_valid) & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_req_accepted));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_21 
        = ((0x6fU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | (0x67U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_7 
        = ((1U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
           | (0U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_22 
        = ((0x37U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | (0x17U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)));
    vlSelfRef.Main__DOT__core__DOT___execute_io_next_instruction_valid 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__valid) 
           & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute_io_flush_REG)) 
              | ((0x6fU == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_opcode)) 
                 | ((0x67U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_opcode)) 
                    | (0x63U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_opcode))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0 = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute_io_flush_REG)) 
                                                & (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__valid));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1 
        = ((0x33U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | (0x13U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)));
    vlSelfRef.Main__DOT___core_io_dcache_rd = (0x0000007fU 
                                               & (((vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                                                    [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U] 
                                                    << 0x0000001cU) 
                                                   | (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                                                      [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][0U] 
                                                      >> 4U)) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT___q_q_io_deq_bits_write)))))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__lookup_address 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__io_mem_req_valid_0)
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__latched_req_addr
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_addr);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10 = ((~ 
                                                  ((2U 
                                                    == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)) 
                                                   | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__read_enable))) 
                                                 & (3U 
                                                    == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__read_enable 
        = ((3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8));
    vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_mask 
        = (1U & ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN) 
                 >> (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_warp)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__read_enable 
        = ((3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state)) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13));
    vlSelfRef.io_blanking = (1U & (~ (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__active)));
    Main__DOT__vga_controller__DOT__vCountShifted = 
        ((IData)(vlSelfRef.Main__DOT__vga_controller__DOT__active)
          ? ((IData)(vlSelfRef.Main__DOT__vga_controller__DOT__vCount) 
             >> 1U) : (0x000001ffU & (((IData)(1U) 
                                       + (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__vCount)) 
                                      >> 1U)));
    vlSelfRef.io_rgb = (((IData)(vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT___R0_en_d0)
                          ? ((0x00012bffU >= vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT___R0_addr_d0)
                              ? vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT__Memory
                             [vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT___R0_addr_d0]
                              : (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT____Vxrand___0))
                          : (IData)(vlSelfRef.Main__DOT__vga_controller__DOT__memory_ext__DOT____Vxrand___1)) 
                        & (- (IData)((IData)(vlSelfRef.Main__DOT__vga_controller__DOT__active))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
        = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data
        [(0x0000000fU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg 
                         >> 2U))];
    vlSelfRef.Main__DOT__core__DOT___execute_io_mark_warp 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_warp) 
           & (- (IData)((1U & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0))))));
    vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__empty 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__maybe_full)) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ptr_match));
    vlSelfRef.Main__DOT__memory__DOT___uartTx_io_in_ready 
        = (1U & (~ ((IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__maybe_full) 
                    & (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ptr_match))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__empty 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__maybe_full)) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ptr_match));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__full 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__maybe_full) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ptr_match));
    vlSelfRef.Main__DOT__memory__DOT__is_keytracker 
        = ((0x08000007U < vlSelfRef.Main__DOT___core_io_dcache_req_address) 
           & (0x08000034U > vlSelfRef.Main__DOT___core_io_dcache_req_address));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_0 
        = ((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__cache_tag_REG 
            == (0x0003ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___meta_array_ext_R0_data)) 
           & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___meta_array_ext_R0_data 
              >> 0x00000013U));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0 
        = (((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg 
             >> 0x0000000eU) == (0x0003ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___meta_array_ext_R0_data)) 
           & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___meta_array_ext_R0_data 
              >> 0x00000013U));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15 = ((0x13U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                                                  ? vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_immediate
                                                  : 
                                                 (((0U 
                                                    == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                                                   & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_14))
                                                   ? 
                                                  (- vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0)
                                                   : vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_19 = (((QData)((IData)(
                                                                  (- (IData)(
                                                                             (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                                                                              >> 0x0000001fU))))) 
                                                  << 0x00000020U) 
                                                 | (QData)((IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_29 
        = ((vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
            << 0x00000010U) | (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                               >> 0x00000010U));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__target_1 
        = (0xfffffffeU & (vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_immediate 
                          + vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__take_branch 
        = (1U & (((4U & (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3))
                   ? ((2U & (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3))
                       ? (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                          < vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0)
                       : VL_LTS_III(32, vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0, vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0))
                   : (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0 
                      == vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0)) 
                 ^ (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_14 
        = ((6U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___slot_T_5 
        = ((2U & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23))
            ? (2U | (1U & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23) 
                           >> 2U))) : 1U);
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_3 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_3) 
            << 3U) | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23));
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__empty 
        = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__maybe_full)) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ptr_match));
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__maybe_full) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ptr_match));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__hit 
        = (((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__lookup_address_reg 
             >> 0x00000010U) == (0x0000ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___meta_array_ext_R0_data)) 
           & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___meta_array_ext_R0_data 
              >> 0x00000011U));
    vlSelfRef.io_mem_req_bits_addr = ((IData)(vlSelfRef.io_mem_req_bits_write)
                                       ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_addr_reg
                                       : (0xffffffc0U 
                                          & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_addr));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5 = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write) 
                                                | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_ack));
    __VdfgRegularize_h6e95ff9d_0_35 = ((2U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
                                       | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_7));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_25 
        = ((0x63U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_22) 
              | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_21)));
    Main__DOT__core__DOT___writeback_io_write_enable 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_rd_wen) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_next_instruction_valid));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_33 = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0) 
                                                 | ((0x0bU 
                                                     != (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                                    | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_2 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__valid) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_23 
        = ((0x0bU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30 = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1)) 
                                                 & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
    vlSelfRef.Main__DOT__vga_controller__DOT___vCountMult_T_2 
        = (0x0001ffffU & ((0x0001ff00U & ((IData)(Main__DOT__vga_controller__DOT__vCountShifted) 
                                          << 8U)) + 
                          ((IData)(Main__DOT__vga_controller__DOT__vCountShifted) 
                           << 6U)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__updated_word 
        = ((5U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data
            : ((6U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
                ? ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                    ? ((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2))
                    : ((0xffff0000U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2) 
                       | (0x0000ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data)))
                : ((7U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
                    ? ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                        ? ((((1U == (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                              ? ((0x00ffff00U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                 >> 8U)) 
                                 | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data))
                              : ((((2U == (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                                    ? ((0x0000ff00U 
                                        & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                           >> 0x00000010U)) 
                                       | (0x000000ffU 
                                          & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data))
                                    : ((0x0000ff00U 
                                        & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data 
                                           << 8U)) 
                                       | (0x000000ffU 
                                          & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                             >> 0x00000010U)))) 
                                  << 8U) | (0x000000ffU 
                                            & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                               >> 8U)))) 
                            << 8U) | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2))
                        : ((0xffffff00U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2) 
                           | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data)))
                    : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2)));
    vlSelfRef.Main__DOT__memory__DOT__uartTx_io_in_valid 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT___uartTx_io_in_ready) 
           & (0x08000034U == vlSelfRef.Main__DOT___core_io_dcache_req_address));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_queue_io_dcache_req_address 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__empty)
            ? vlSelfRef.Main__DOT___core_io_dcache_req_address
            : ((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory
                [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__deq_ptr_value][2U] 
                << 0x00000014U) | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory
                                   [vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__deq_ptr_value][1U] 
                                   >> 0x0000000cU)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_41 = ((IData)(vlSelfRef.Main__DOT__memory__DOT__bypass_pending) 
                                                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__full));
    vlSelfRef.Main__DOT__memory__DOT__is_excep = ((0U 
                                                   != 
                                                   (vlSelfRef.Main__DOT___core_io_dcache_req_address 
                                                    >> 0x0000001cU)) 
                                                  | ((0x08000004U 
                                                      == vlSelfRef.Main__DOT___core_io_dcache_req_address) 
                                                     | ((IData)(vlSelfRef.Main__DOT__memory__DOT__is_keytracker) 
                                                        | ((0x08000034U 
                                                            == vlSelfRef.Main__DOT___core_io_dcache_req_address) 
                                                           | ((0x70000000U 
                                                               == vlSelfRef.Main__DOT___core_io_dcache_req_address) 
                                                              | ((0x70000008U 
                                                                  == vlSelfRef.Main__DOT___core_io_dcache_req_address) 
                                                                 | (0x09000000U 
                                                                    == vlSelfRef.Main__DOT___core_io_dcache_req_address)))))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__io_ready_0 
        = (1U & ((~ (0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state))) 
                 | ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)) 
                    & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_0))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_7 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_39 
        = ((0xff00ff00U & (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_29 
                           << 8U)) | (0x00ff00ffU & 
                                      (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_29 
                                       >> 8U)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__target 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__take_branch)
            ? vlSelfRef.Main__DOT__core__DOT__execute__DOT___pc_plus_imm_T
            : ((IData)(4U) + vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_pc));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_0 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN) 
           & (0x0fU != (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_3)));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_5 
        = (1U & ((~ ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_3) 
                     >> (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warp))) 
                 | ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_4) 
                    >> (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warp))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_29 
        = ((3U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
            ? (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full)
            : ((0x23U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
               & (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_0 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__hit));
    vlSelfRef.io_mem_req_valid = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_req_accepted)) 
                                  & ((IData)(vlSelfRef.io_mem_req_bits_write) 
                                     | ((~ ((IData)(vlSelfRef.io_mem_req_bits_write) 
                                            | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_13) 
                                               | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5)))) 
                                        & (3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state)))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_5 
        = (1U & ((~ ((3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state)) 
                     & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5))) 
                 | (IData)(vlSelfRef.io_mem_req_bits_write)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_3 
        = ((~ ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_5)) 
               | (IData)(vlSelfRef.io_mem_req_bits_write))) 
           & (3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_11 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_35) 
           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_15 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_35) 
           | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_14));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_26 
        = ((0x0bU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
           | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_25));
    vlSelfRef.Main__DOT__core__DOT__registers__DOT__w1 
        = ((0U != (0x0000001fU & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_rd))) 
           & (IData)(Main__DOT__core__DOT___writeback_io_write_enable));
    __Vtemp_1[0U] = vlSelfRef.Main__DOT__core__DOT___execute_io_next_instruction_valid;
    __Vtemp_1[1U] = 0U;
    __Vtemp_1[2U] = 0U;
    __Vtemp_1[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_2, __Vtemp_1, (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_rd));
    __Vtemp_3[0U] = vlSelfRef.Main__DOT__core__DOT__read__DOT__valid;
    __Vtemp_3[1U] = 0U;
    __Vtemp_3[2U] = 0U;
    __Vtemp_3[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_4, __Vtemp_3, (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_rd));
    __Vtemp_5[0U] = Main__DOT__core__DOT___writeback_io_write_enable;
    __Vtemp_5[1U] = 0U;
    __Vtemp_5[2U] = 0U;
    __Vtemp_5[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_6, __Vtemp_5, (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_rd));
    __Vtemp_7[0U] = (((((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_63)) 
                            << 3U) | ((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_62)) 
                                      << 2U)) | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_61)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_60)))) 
                         << 0x0000000cU) | (((((0U 
                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_59)) 
                                               << 3U) 
                                              | ((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_58)) 
                                                 << 2U)) 
                                             | (((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_57)) 
                                                 << 1U) 
                                                | (0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_56)))) 
                                            << 8U)) 
                       | ((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_55)) 
                              << 3U) | ((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_54)) 
                                        << 2U)) | (
                                                   ((0U 
                                                     != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_53)) 
                                                    << 1U) 
                                                   | (0U 
                                                      != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_52)))) 
                           << 4U) | ((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_51)) 
                                       << 3U) | ((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_50)) 
                                                 << 2U)) 
                                     | (((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_49)) 
                                         << 1U) | (0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_48)))))) 
                      << 0x00000010U) | (((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_47)) 
                                              << 3U) 
                                             | ((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_46)) 
                                                << 2U)) 
                                            | (((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_45)) 
                                                << 1U) 
                                               | (0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_44)))) 
                                           << 0x0000000cU) 
                                          | (((((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_43)) 
                                                << 3U) 
                                               | ((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_42)) 
                                                  << 2U)) 
                                              | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_41)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_40)))) 
                                             << 8U)) 
                                         | ((((((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_39)) 
                                                << 3U) 
                                               | ((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_38)) 
                                                  << 2U)) 
                                              | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_37)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_36)))) 
                                             << 4U) 
                                            | ((((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_35)) 
                                                 << 3U) 
                                                | ((0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_34)) 
                                                   << 2U)) 
                                               | (((0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_33)) 
                                                   << 1U) 
                                                  | (0U 
                                                     != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_32)))))));
    __Vtemp_7[1U] = (IData)((((QData)((IData)((((((
                                                   ((((0U 
                                                       != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_127)) 
                                                      << 3U) 
                                                     | ((0U 
                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_126)) 
                                                        << 2U)) 
                                                    | (((0U 
                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_125)) 
                                                        << 1U) 
                                                       | (0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_124)))) 
                                                   << 0x0000000cU) 
                                                  | (((((0U 
                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_123)) 
                                                        << 3U) 
                                                       | ((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_122)) 
                                                          << 2U)) 
                                                      | (((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_121)) 
                                                          << 1U) 
                                                         | (0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_120)))) 
                                                     << 8U)) 
                                                 | ((((((0U 
                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_119)) 
                                                        << 3U) 
                                                       | ((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_118)) 
                                                          << 2U)) 
                                                      | (((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_117)) 
                                                          << 1U) 
                                                         | (0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_116)))) 
                                                     << 4U) 
                                                    | ((((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_115)) 
                                                         << 3U) 
                                                        | ((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_114)) 
                                                           << 2U)) 
                                                       | (((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_113)) 
                                                           << 1U) 
                                                          | (0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_112)))))) 
                                                << 0x00000010U) 
                                               | (((((((0U 
                                                        != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_111)) 
                                                       << 3U) 
                                                      | ((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_110)) 
                                                         << 2U)) 
                                                     | (((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_109)) 
                                                         << 1U) 
                                                        | (0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_108)))) 
                                                    << 0x0000000cU) 
                                                   | (((((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_107)) 
                                                         << 3U) 
                                                        | ((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_106)) 
                                                           << 2U)) 
                                                       | (((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_105)) 
                                                           << 1U) 
                                                          | (0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_104)))) 
                                                      << 8U)) 
                                                  | ((((((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_103)) 
                                                         << 3U) 
                                                        | ((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_102)) 
                                                           << 2U)) 
                                                       | (((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_101)) 
                                                           << 1U) 
                                                          | (0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_100)))) 
                                                      << 4U) 
                                                     | ((((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_99)) 
                                                          << 3U) 
                                                         | ((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_98)) 
                                                            << 2U)) 
                                                        | (((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_97)) 
                                                            << 1U) 
                                                           | (0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_96))))))))) 
                              << 0x00000020U) | (QData)((IData)(
                                                                (((((((((0U 
                                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_95)) 
                                                                        << 3U) 
                                                                       | ((0U 
                                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_94)) 
                                                                          << 2U)) 
                                                                      | (((0U 
                                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_93)) 
                                                                          << 1U) 
                                                                         | (0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_92)))) 
                                                                     << 0x0000000cU) 
                                                                    | (((((0U 
                                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_91)) 
                                                                          << 3U) 
                                                                         | ((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_90)) 
                                                                            << 2U)) 
                                                                        | (((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_89)) 
                                                                            << 1U) 
                                                                           | (0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_88)))) 
                                                                       << 8U)) 
                                                                   | ((((((0U 
                                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_87)) 
                                                                          << 3U) 
                                                                         | ((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_86)) 
                                                                            << 2U)) 
                                                                        | (((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_85)) 
                                                                            << 1U) 
                                                                           | (0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_84)))) 
                                                                       << 4U) 
                                                                      | ((((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_83)) 
                                                                           << 3U) 
                                                                          | ((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_82)) 
                                                                             << 2U)) 
                                                                         | (((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_81)) 
                                                                             << 1U) 
                                                                            | (0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_80)))))) 
                                                                  << 0x00000010U) 
                                                                 | (((((((0U 
                                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_79)) 
                                                                         << 3U) 
                                                                        | ((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_78)) 
                                                                           << 2U)) 
                                                                       | (((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_77)) 
                                                                           << 1U) 
                                                                          | (0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_76)))) 
                                                                      << 0x0000000cU) 
                                                                     | (((((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_75)) 
                                                                           << 3U) 
                                                                          | ((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_74)) 
                                                                             << 2U)) 
                                                                         | (((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_73)) 
                                                                             << 1U) 
                                                                            | (0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_72)))) 
                                                                        << 8U)) 
                                                                    | ((((((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_71)) 
                                                                           << 3U) 
                                                                          | ((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_70)) 
                                                                             << 2U)) 
                                                                         | (((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_69)) 
                                                                             << 1U) 
                                                                            | (0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_68)))) 
                                                                        << 4U) 
                                                                       | ((((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_67)) 
                                                                            << 3U) 
                                                                           | ((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_66)) 
                                                                              << 2U)) 
                                                                          | (((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_65)) 
                                                                              << 1U) 
                                                                             | (0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_64)))))))))));
    __Vtemp_7[2U] = (IData)(((((QData)((IData)(((((
                                                   (((((0U 
                                                        != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_127)) 
                                                       << 3U) 
                                                      | ((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_126)) 
                                                         << 2U)) 
                                                     | (((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_125)) 
                                                         << 1U) 
                                                        | (0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_124)))) 
                                                    << 0x0000000cU) 
                                                   | (((((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_123)) 
                                                         << 3U) 
                                                        | ((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_122)) 
                                                           << 2U)) 
                                                       | (((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_121)) 
                                                           << 1U) 
                                                          | (0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_120)))) 
                                                      << 8U)) 
                                                  | ((((((0U 
                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_119)) 
                                                         << 3U) 
                                                        | ((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_118)) 
                                                           << 2U)) 
                                                       | (((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_117)) 
                                                           << 1U) 
                                                          | (0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_116)))) 
                                                      << 4U) 
                                                     | ((((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_115)) 
                                                          << 3U) 
                                                         | ((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_114)) 
                                                            << 2U)) 
                                                        | (((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_113)) 
                                                            << 1U) 
                                                           | (0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_112)))))) 
                                                 << 0x00000010U) 
                                                | (((((((0U 
                                                         != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_111)) 
                                                        << 3U) 
                                                       | ((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_110)) 
                                                          << 2U)) 
                                                      | (((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_109)) 
                                                          << 1U) 
                                                         | (0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_108)))) 
                                                     << 0x0000000cU) 
                                                    | (((((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_107)) 
                                                          << 3U) 
                                                         | ((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_106)) 
                                                            << 2U)) 
                                                        | (((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_105)) 
                                                            << 1U) 
                                                           | (0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_104)))) 
                                                       << 8U)) 
                                                   | ((((((0U 
                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_103)) 
                                                          << 3U) 
                                                         | ((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_102)) 
                                                            << 2U)) 
                                                        | (((0U 
                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_101)) 
                                                            << 1U) 
                                                           | (0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_100)))) 
                                                       << 4U) 
                                                      | ((((0U 
                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_99)) 
                                                           << 3U) 
                                                          | ((0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_98)) 
                                                             << 2U)) 
                                                         | (((0U 
                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_97)) 
                                                             << 1U) 
                                                            | (0U 
                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_96))))))))) 
                               << 0x00000020U) | (QData)((IData)(
                                                                 (((((((((0U 
                                                                          != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_95)) 
                                                                         << 3U) 
                                                                        | ((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_94)) 
                                                                           << 2U)) 
                                                                       | (((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_93)) 
                                                                           << 1U) 
                                                                          | (0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_92)))) 
                                                                      << 0x0000000cU) 
                                                                     | (((((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_91)) 
                                                                           << 3U) 
                                                                          | ((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_90)) 
                                                                             << 2U)) 
                                                                         | (((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_89)) 
                                                                             << 1U) 
                                                                            | (0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_88)))) 
                                                                        << 8U)) 
                                                                    | ((((((0U 
                                                                            != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_87)) 
                                                                           << 3U) 
                                                                          | ((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_86)) 
                                                                             << 2U)) 
                                                                         | (((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_85)) 
                                                                             << 1U) 
                                                                            | (0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_84)))) 
                                                                        << 4U) 
                                                                       | ((((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_83)) 
                                                                            << 3U) 
                                                                           | ((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_82)) 
                                                                              << 2U)) 
                                                                          | (((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_81)) 
                                                                              << 1U) 
                                                                             | (0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_80)))))) 
                                                                   << 0x00000010U) 
                                                                  | (((((((0U 
                                                                           != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_79)) 
                                                                          << 3U) 
                                                                         | ((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_78)) 
                                                                            << 2U)) 
                                                                        | (((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_77)) 
                                                                            << 1U) 
                                                                           | (0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_76)))) 
                                                                       << 0x0000000cU) 
                                                                      | (((((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_75)) 
                                                                            << 3U) 
                                                                           | ((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_74)) 
                                                                              << 2U)) 
                                                                          | (((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_73)) 
                                                                              << 1U) 
                                                                             | (0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_72)))) 
                                                                         << 8U)) 
                                                                     | ((((((0U 
                                                                             != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_71)) 
                                                                            << 3U) 
                                                                           | ((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_70)) 
                                                                              << 2U)) 
                                                                          | (((0U 
                                                                               != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_69)) 
                                                                              << 1U) 
                                                                             | (0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_68)))) 
                                                                         << 4U) 
                                                                        | ((((0U 
                                                                              != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_67)) 
                                                                             << 3U) 
                                                                            | ((0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_66)) 
                                                                               << 2U)) 
                                                                           | (((0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_65)) 
                                                                               << 1U) 
                                                                              | (0U 
                                                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_64)))))))))) 
                             >> 0x00000020U));
    __Vtemp_8[0U] = (((((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_31)) 
                            << 3U) | ((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_30)) 
                                      << 2U)) | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_29)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_28)))) 
                         << 0x0000000cU) | (((((0U 
                                                != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_27)) 
                                               << 3U) 
                                              | ((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_26)) 
                                                 << 2U)) 
                                             | (((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_25)) 
                                                 << 1U) 
                                                | (0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_24)))) 
                                            << 8U)) 
                       | ((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_23)) 
                              << 3U) | ((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_22)) 
                                        << 2U)) | (
                                                   ((0U 
                                                     != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_21)) 
                                                    << 1U) 
                                                   | (0U 
                                                      != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_20)))) 
                           << 4U) | ((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_19)) 
                                       << 3U) | ((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_18)) 
                                                 << 2U)) 
                                     | (((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_17)) 
                                         << 1U) | (0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_16)))))) 
                      << 0x00000010U) | (((((((0U != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_15)) 
                                              << 3U) 
                                             | ((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_14)) 
                                                << 2U)) 
                                            | (((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_13)) 
                                                << 1U) 
                                               | (0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_12)))) 
                                           << 0x0000000cU) 
                                          | (((((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_11)) 
                                                << 3U) 
                                               | ((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_10)) 
                                                  << 2U)) 
                                              | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_9)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_8)))) 
                                             << 8U)) 
                                         | ((((((0U 
                                                 != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_7)) 
                                                << 3U) 
                                               | ((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_6)) 
                                                  << 2U)) 
                                              | (((0U 
                                                   != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_5)) 
                                                  << 1U) 
                                                 | (0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_4)))) 
                                             << 4U) 
                                            | ((((0U 
                                                  != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_3)) 
                                                 << 3U) 
                                                | ((0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_2)) 
                                                   << 2U)) 
                                               | (((0U 
                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_1)) 
                                                   << 1U) 
                                                  | (0U 
                                                     != (IData)(vlSelfRef.Main__DOT__core__DOT__writeback__DOT__mem_pending_0)))))));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum[0U] 
        = (__Vtemp_2[0U] | (__Vtemp_4[0U] | (__Vtemp_6[0U] 
                                             | __Vtemp_8[0U])));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum[1U] 
        = (__Vtemp_2[1U] | (__Vtemp_4[1U] | (__Vtemp_6[1U] 
                                             | __Vtemp_7[0U])));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum[2U] 
        = (__Vtemp_2[2U] | (__Vtemp_4[2U] | (__Vtemp_6[2U] 
                                             | __Vtemp_7[1U])));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum[3U] 
        = (__Vtemp_2[3U] | (__Vtemp_4[3U] | (__Vtemp_6[3U] 
                                             | __Vtemp_7[2U])));
}

extern const VlWide<16>/*511:0*/ VMain__ConstPool__CONST_h93e1b771_0;

VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__2(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___stl_sequent__TOP__2\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_59;
    Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_59 = 0;
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    // Body
    vlSelfRef.Main__DOT__core__DOT__execute__DOT____Vcellinp__malus_0__io_start 
        = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute_io_flush_REG)) 
           & ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_2) 
              & ((~ (0U != (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state))) 
                 & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__isM))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36 = (1U 
                                                 & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_2)) 
                                                    | (IData)(vlSelfRef.Main__DOT__core__DOT__execute_io_flush_REG)));
    vlSelfRef.Main__DOT__core__DOT___execute_io_jump_flush 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0) 
           & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_23)) 
              & ((0x63U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                  ? (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__take_branch)
                  : ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_22)) 
                     & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_21)))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4 = ((0x0bU 
                                                 == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                                & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30));
    vlSelfRef.Main__DOT__memory__DOT____Vcellinp__uartTx__io_in_bits 
        = (0x000000ffU & ((- (IData)((IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx_io_in_valid))) 
                          & ((vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                              [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][1U] 
                              << 0x00000014U) | (vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory
                                                 [vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value][1U] 
                                                 >> 0x0000000cU))));
    vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__do_enq 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT___uartTx_io_in_ready) 
           & ((~ ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__busy)) 
                  & (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__empty))) 
              & (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx_io_in_valid)));
    vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__io_deq_valid_0 
        = (1U & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__empty)) 
                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx_io_in_valid)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_40 = ((IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__empty) 
                                                 | ((IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__active) 
                                                    & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_41)));
    vlSelfRef.Main__DOT___core_io_dcache_start = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__empty)) 
                                                  & ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_41)) 
                                                     & (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__active)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_49 
        = ((0xf0f0f0f0U & (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_39 
                           << 4U)) | (0x0f0f0f0fU & 
                                      (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_39 
                                       >> 4U)));
    vlSelfRef.Main__DOT__core__DOT___execute_io_mark_pc 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_23)
             ? ((IData)(4U) + vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_pc)
             : ((0x63U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                 ? vlSelfRef.Main__DOT__core__DOT__execute__DOT__target
                 : ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_22)
                     ? ((IData)(4U) + vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_pc)
                     : ((0x6fU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                         ? vlSelfRef.Main__DOT__core__DOT__execute__DOT___pc_plus_imm_T
                         : ((0x67U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                             ? vlSelfRef.Main__DOT__core__DOT__execute__DOT__target_1
                             : ((IData)(4U) + vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_pc)))))) 
           & (- (IData)((1U & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0))))));
    vlSelfRef.Main__DOT__core__DOT___execute_io_pc_redirect_bits 
        = (((0x63U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
             ? vlSelfRef.Main__DOT__core__DOT__execute__DOT__target
             : (((0x6fU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                  ? vlSelfRef.Main__DOT__core__DOT__execute__DOT___pc_plus_imm_T
                  : ((- (IData)((0x67U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)))) 
                     & vlSelfRef.Main__DOT__core__DOT__execute__DOT__target_1)) 
                & (- (IData)((1U & (~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_22))))))) 
           & (- (IData)((1U & (~ ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0) 
                                  | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_23)))))));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_1 
        = ((IData)(vlSelfRef.io_execute) & (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_0));
    if ((0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state))) {
        if ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state))) {
            if ((1U & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__hit)) 
                       | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write)))) {
                VL_ASSIGN_W(512, vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5, VMain__ConstPool__CONST_h93e1b771_0);
            } else {
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[0U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[0U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[1U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[1U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[2U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[2U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[3U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[3U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[4U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[4U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[5U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[5U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[6U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[6U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[7U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[7U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[8U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[8U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[9U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[9U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[10U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[10U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[11U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[11U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[12U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[12U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[13U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[13U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[14U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[14U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[15U] 
                    = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data[15U];
            }
            vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT____Vcellinp__meta_array_ext__W0_en 
                = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_0;
            vlSelfRef.Main__DOT__memory__DOT__mem__DOT___l2_cache_io_mem_valid_in 
                = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__hit;
        } else {
            if (((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write) 
                 | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_5))) {
                VL_ASSIGN_W(512, vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5, VMain__ConstPool__CONST_h93e1b771_0);
            } else {
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[0U] 
                    = vlSelfRef.io_mem_resp[0U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[1U] 
                    = vlSelfRef.io_mem_resp[1U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[2U] 
                    = vlSelfRef.io_mem_resp[2U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[3U] 
                    = vlSelfRef.io_mem_resp[3U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[4U] 
                    = vlSelfRef.io_mem_resp[4U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[5U] 
                    = vlSelfRef.io_mem_resp[5U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[6U] 
                    = vlSelfRef.io_mem_resp[6U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[7U] 
                    = vlSelfRef.io_mem_resp[7U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[8U] 
                    = vlSelfRef.io_mem_resp[8U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[9U] 
                    = vlSelfRef.io_mem_resp[9U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[10U] 
                    = vlSelfRef.io_mem_resp[10U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[11U] 
                    = vlSelfRef.io_mem_resp[11U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[12U] 
                    = vlSelfRef.io_mem_resp[12U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[13U] 
                    = vlSelfRef.io_mem_resp[13U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[14U] 
                    = vlSelfRef.io_mem_resp[14U];
                vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5[15U] 
                    = vlSelfRef.io_mem_resp[15U];
            }
            vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT____Vcellinp__meta_array_ext__W0_en 
                = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_3;
            vlSelfRef.Main__DOT__memory__DOT__mem__DOT___l2_cache_io_mem_valid_in 
                = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_3;
        }
    } else {
        VL_ASSIGN_W(512, vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5, VMain__ConstPool__CONST_h93e1b771_0);
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT____Vcellinp__meta_array_ext__W0_en = 0U;
        vlSelfRef.Main__DOT__memory__DOT__mem__DOT___l2_cache_io_mem_valid_in = 0U;
    }
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_28 = (- (IData)(
                                                           (1U 
                                                            & (~ 
                                                               ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_33) 
                                                                | ((6U 
                                                                    != (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
                                                                   | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_11)))))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_27 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1) 
           | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_26));
    vlSelfRef.Main__DOT__core__DOT___execute_io_memory_stall 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_1)
             ? ((~ ((~ ((7U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                        | ((6U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                           | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20)))) 
                    | ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT___GEN_1)) 
                       & (2U == (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state))))) 
                & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__isM))
             : ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_26)) 
                & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_29))) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
    VL_SHIFTR_WWI(128,128,7, __Vtemp_1, vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum, (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rs1));
    VL_SHIFTR_WWI(128,128,7, __Vtemp_2, vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum, (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rs2));
    VL_SHIFTR_WWI(128,128,7, __Vtemp_3, vlSelfRef.Main__DOT__core__DOT____Vcellinp__read__io_rum, (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rd));
    vlSelfRef.Main__DOT__core__DOT__read__DOT__raw_hazard 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__valid) 
           & ((__Vtemp_1[0U] & (0U != (0x0000001fU 
                                       & (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rs1)))) 
              | ((__Vtemp_2[0U] & (0U != (0x0000001fU 
                                          & (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rs2)))) 
                 | ((IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__wen) 
                    & (__Vtemp_3[0U] & (0U != (0x0000001fU 
                                               & (IData)(vlSelfRef.Main__DOT__core__DOT__decode__DOT__rd))))))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__malus_0__DOT____Vcellinp__div__io_start 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT____Vcellinp__malus_0__io_start) 
           & ((~ ((0U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                  | ((1U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                     | ((2U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                        | (3U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)))))) 
              & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20) 
                 | ((6U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3)) 
                    | (7U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func3))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_3 = ((~ vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15) 
                                                | (- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0_io_b 
        = (vlSelfRef.__VdfgRegularize_h6e95ff9d_0_15 
           & (- (IData)((1U & (~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_36))))));
    vlSelfRef.Main__DOT__core__DOT___execute_io_spawn 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_11)) 
              & (6U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7))));
    vlSelfRef.Main__DOT__core__DOT___execute_io_warp_terminate 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_7)) 
              & (2U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7))));
    vlSelfRef.Main__DOT__core__DOT___execute_io_barrier 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_4) 
           & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_15)) 
              & (7U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7))));
    vlSelfRef.io_txd = (1U & ((IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__busy)
                               ? (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__shiftReg)
                               : (~ (IData)(vlSelfRef.Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__io_deq_valid_0))));
    vlSelfRef.Main__DOT__memory__DOT____Vcellinp__mem__io_dcache_start 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__is_excep)) 
           & (IData)(vlSelfRef.Main__DOT___core_io_dcache_start));
    Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_59 
        = ((0xccccccccU & (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_49 
                           << 2U)) | (0x33333333U & 
                                      (vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_49 
                                       >> 2U)));
    vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_allocate_warp 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_1));
    vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_allocate_pc 
        = (vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__spawn_pc 
           & (- (IData)((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_1))));
    vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_allocate_id 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___slot_T_5) 
           & (- (IData)((1U & (~ ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_1)) 
                                  | (~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_23))))))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
        = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5
        [(0x0000000fU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg 
                         >> 2U))];
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT___io_resp_to_cache_1_T 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__busy) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___l2_cache_io_mem_valid_in));
    vlSelfRef.Main__DOT__core__DOT___execute_io_mem_issue_rd 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_rd) 
           & (- (IData)((1U & (~ ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_0) 
                                  | ((3U != (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                     | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_27))))))));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__io_mark_0 
        = (((~ ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16) 
                & (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full))) 
            | (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_27)) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32 = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_27)) 
                                                 & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_0));
    vlSelfRef.Main__DOT__core__DOT__fetch_stall = (1U 
                                                   & ((IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__raw_hazard) 
                                                      | ((~ (IData)(vlSelfRef.io_execute)) 
                                                         | (IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_memory_stall))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_21 = (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                                                 < vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0_io_b);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_22 = VL_LTS_III(32, vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0, vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0_io_b);
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_26 = (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                                                 << 
                                                 (0x0000001fU 
                                                  & vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0_io_b));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_27 = (vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 
                                                 >> 
                                                 (0x0000001fU 
                                                  & vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0_io_b));
    vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_2 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_warp_terminate) 
            | ((0U != ((~ ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_4) 
                           | ((IData)(1U) << (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warp)))) 
                       & (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_3))) 
               | (IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_barrier))) 
           & (((0x0bU == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode))
                ? ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_7)) 
                   & ((2U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)) 
                      | ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_14)) 
                         & (7U == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_func7)))))
                : ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_25)) 
                   & (IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT___GEN_29))) 
              & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__io_deq_valid_0 
        = (1U & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__empty)) 
                 | (IData)(vlSelfRef.Main__DOT__memory__DOT____Vcellinp__mem__io_dcache_start)));
    vlSelfRef.Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_69 
        = ((0x55555555U & (Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_59 
                           >> 1U)) | (0x2aaaaaaaU & 
                                      (Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_59 
                                       << 1U)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__updated_word_1 
        = ((5U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data
            : ((6U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
                ? ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                    ? ((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data 
                        << 0x00000010U) | (0x0000ffffU 
                                           & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13))
                    : ((0xffff0000U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13) 
                       | (0x0000ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data)))
                : ((7U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))
                    ? ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                        ? ((((1U == (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                              ? ((0x00ffff00U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                 >> 8U)) 
                                 | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data))
                              : ((((2U == (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))
                                    ? ((0x0000ff00U 
                                        & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                           >> 0x00000010U)) 
                                       | (0x000000ffU 
                                          & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data))
                                    : ((0x0000ff00U 
                                        & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data 
                                           << 8U)) 
                                       | (0x000000ffU 
                                          & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                             >> 0x00000010U)))) 
                                  << 8U) | (0x000000ffU 
                                            & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                               >> 8U)))) 
                            << 8U) | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13))
                        : ((0xffffff00U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13) 
                           | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data)))
                    : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_1 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__owner) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT___io_resp_to_cache_1_T));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_0 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__owner)) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__arbiter__DOT___io_resp_to_cache_1_T));
    vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__do_enq 
        = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full)) 
           & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16) 
              & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31 = ((3U 
                                                  == (IData)(vlSelfRef.Main__DOT__core__DOT__read__DOT__bundle_opcode)) 
                                                 & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_32));
    vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_warp_swap_flush 
        = ((IData)(vlSelfRef.io_execute) & ((IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_2) 
                                            | (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT___GEN_5)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__io_dcache_start_0 
        = (((~ (0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))) 
            | ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
               & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write)) 
                  & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0)))) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__io_deq_valid_0));
}

VL_ATTR_COLD void VMain___024root___stl_sequent__TOP__3(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___stl_sequent__TOP__3\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_15;
    Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_15 = 0;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<8>/*255:0*/ __Vtemp_9;
    VlWide<4>/*127:0*/ __Vtemp_12;
    VlWide<4>/*127:0*/ __Vtemp_15;
    VlWide<8>/*255:0*/ __Vtemp_18;
    // Body
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_4 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10) 
           & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_write)) 
              & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_1)));
    vlSelfRef.Main__DOT___memory_io_icache_valid = 
        ((0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)) 
         & ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state))
             ? (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_0)
             : ((3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)) 
                & ((2U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__state)) 
                   & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_1)))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_6 = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__valid_cleared) 
                                                & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_0));
    vlSelfRef.Main__DOT__core__DOT___execute_io_mem_issue 
        = ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full)) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__writeback__io_mem_issue_count 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_lsu_req_bits_mask) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31));
    vlSelfRef.Main__DOT__core__DOT__read_io_flush = 
        ((IData)(vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_warp_swap_flush) 
         | (IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_jump_flush));
    vlSelfRef.Main__DOT__core__DOT____Vcellinp__fetch__io_fetch_request_fetch_op 
        = (3U & (((IData)(vlSelfRef.Main__DOT__core__DOT___execute_io_jump_flush)
                   ? 1U : (2U & ((~ (IData)(vlSelfRef.Main__DOT__core__DOT__fetch_stall)) 
                                 << 1U))) | (- (IData)((IData)(vlSelfRef.Main__DOT__core__DOT___warp_scheduler_io_warp_swap_flush)))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address 
        = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__io_dcache_start_0)
            ? vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_queue_io_dcache_req_address
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_address);
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__do_enq 
        = ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__full)) 
           & ((~ ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__empty) 
                  & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__io_dcache_start_0))) 
              & (IData)(vlSelfRef.Main__DOT__memory__DOT____Vcellinp__mem__io_dcache_start)));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT__can_issue 
        = ((~ ((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__fetch_result_valid) 
               | (IData)(vlSelfRef.Main__DOT___memory_io_icache_valid))) 
           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__io_ready_0));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT____Vcellinp__arbiter__io_cache_req_0_valid 
        = ((2U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
           | ((~ ((2U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
                  | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_6) 
                     | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_8)))) 
              & (3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_17 
        = (1U & ((~ ((3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
                     & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_6))) 
                 | (2U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))));
    Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_15 
        = ((~ ((~ (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_6)) 
               | (2U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)))) 
           & (3U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT__dequeuing 
        = ((IData)(vlSelfRef.io_execute) & (2U == (IData)(vlSelfRef.Main__DOT__core__DOT____Vcellinp__fetch__io_fetch_request_fetch_op)));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT__redirecting 
        = ((IData)(vlSelfRef.io_execute) & (1U == (IData)(vlSelfRef.Main__DOT__core__DOT____Vcellinp__fetch__io_fetch_request_fetch_op)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT____Vcellinp__meta_array_ext__W0_en 
        = ((0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
           & ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))
               ? (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_7)
               : (IData)(Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_15)));
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_io_done 
        = ((0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state)) 
           & ((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))
               ? (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0)
               : (IData)(Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_15)));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN_0 
        = (((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__dequeuing) 
            | ((IData)(vlSelfRef.io_execute) & (0U 
                                                == (IData)(vlSelfRef.Main__DOT__core__DOT____Vcellinp__fetch__io_fetch_request_fetch_op)))) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__can_issue));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN_1 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__redirecting) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__can_issue));
    vlSelfRef.Main__DOT__memory__DOT__bypass_fire = 
        ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_io_done)) 
         & (IData)(vlSelfRef.Main__DOT__memory__DOT__bypass_pending));
    vlSelfRef.Main__DOT__core__DOT__fetch__DOT__io_icache_start_0 
        = ((IData)(vlSelfRef.io_execute) & ((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN_0) 
                                            | (IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN_1)));
    vlSelfRef.Main__DOT___core_io_icache_req_address 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN_1)
            ? vlSelfRef.Main__DOT__core__DOT___execute_io_pc_redirect_bits
            : vlSelfRef.Main__DOT__core__DOT__fetch__DOT___GEN
           [(0x07ffffffU & (IData)(vlSelfRef.Main__DOT__core__DOT__warp_scheduler__DOT__active_warp))]);
    __Vtemp_3[0U] = 0U;
    __Vtemp_3[1U] = (0x000000ffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                    >> 8U));
    __Vtemp_3[2U] = (IData)((((QData)((IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                               >> 0x00000018U))) 
                              << 0x00000020U) | (QData)((IData)(
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                    >> 0x00000010U))))));
    __Vtemp_3[3U] = (IData)(((((QData)((IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                >> 0x00000018U))) 
                               << 0x00000020U) | (QData)((IData)(
                                                                 (0x000000ffU 
                                                                  & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                     >> 0x00000010U))))) 
                             >> 0x00000020U));
    __Vtemp_6[0U] = 0U;
    __Vtemp_6[1U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                        >> 0x0000000fU)))) 
                      << 8U) | (0x000000ffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                               >> 8U)));
    __Vtemp_6[2U] = (IData)((((QData)((IData)((((- (IData)(
                                                           (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                            >> 0x0000001fU))) 
                                                << 8U) 
                                               | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                  >> 0x00000018U)))) 
                              << 0x00000020U) | (QData)((IData)(
                                                                (((- (IData)(
                                                                             (1U 
                                                                              & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                                >> 0x00000017U)))) 
                                                                  << 8U) 
                                                                 | (0x000000ffU 
                                                                    & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                       >> 0x00000010U)))))));
    __Vtemp_6[3U] = (IData)(((((QData)((IData)((((- (IData)(
                                                            (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                             >> 0x0000001fU))) 
                                                 << 8U) 
                                                | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                   >> 0x00000018U)))) 
                               << 0x00000020U) | (QData)((IData)(
                                                                 (((- (IData)(
                                                                              (1U 
                                                                               & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                                >> 0x00000017U)))) 
                                                                   << 8U) 
                                                                  | (0x000000ffU 
                                                                     & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                                                        >> 0x00000010U)))))) 
                             >> 0x00000020U));
    __Vtemp_9[0U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2;
    if ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))) {
        __Vtemp_9[1U] = (((- (IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                      >> 0x0000001fU))) 
                          << 0x00000010U) | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                             >> 0x00000010U));
        __Vtemp_9[2U] = __Vtemp_6[(3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg)];
        __Vtemp_9[3U] = __Vtemp_3[(3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg)];
        __Vtemp_9[4U] = (0x0000ffffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                        >> 0x00000010U));
    } else {
        __Vtemp_9[1U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                            >> 0x0000000fU)))) 
                          << 0x00000010U) | (0x0000ffffU 
                                             & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2));
        __Vtemp_9[2U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 
                                            >> 7U)))) 
                          << 8U) | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2));
        __Vtemp_9[3U] = (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2);
        __Vtemp_9[4U] = (0x0000ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2);
    }
    __Vtemp_9[5U] = 0U;
    __Vtemp_9[6U] = 0U;
    __Vtemp_9[7U] = 0U;
    __Vtemp_12[0U] = 0U;
    __Vtemp_12[1U] = (0x000000ffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                     >> 8U));
    __Vtemp_12[2U] = (IData)((((QData)((IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                >> 0x00000018U))) 
                               << 0x00000020U) | (QData)((IData)(
                                                                 (0x000000ffU 
                                                                  & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                     >> 0x00000010U))))));
    __Vtemp_12[3U] = (IData)(((((QData)((IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                 >> 0x00000018U))) 
                                << 0x00000020U) | (QData)((IData)(
                                                                  (0x000000ffU 
                                                                   & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                      >> 0x00000010U))))) 
                              >> 0x00000020U));
    __Vtemp_15[0U] = 0U;
    __Vtemp_15[1U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                         >> 0x0000000fU)))) 
                       << 8U) | (0x000000ffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                >> 8U)));
    __Vtemp_15[2U] = (IData)((((QData)((IData)((((- (IData)(
                                                            (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                             >> 0x0000001fU))) 
                                                 << 8U) 
                                                | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                   >> 0x00000018U)))) 
                               << 0x00000020U) | (QData)((IData)(
                                                                 (((- (IData)(
                                                                              (1U 
                                                                               & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                                >> 0x00000017U)))) 
                                                                   << 8U) 
                                                                  | (0x000000ffU 
                                                                     & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                        >> 0x00000010U)))))));
    __Vtemp_15[3U] = (IData)(((((QData)((IData)((((- (IData)(
                                                             (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                              >> 0x0000001fU))) 
                                                  << 8U) 
                                                 | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                    >> 0x00000018U)))) 
                                << 0x00000020U) | (QData)((IData)(
                                                                  (((- (IData)(
                                                                               (1U 
                                                                                & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                                >> 0x00000017U)))) 
                                                                    << 8U) 
                                                                   | (0x000000ffU 
                                                                      & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                                                         >> 0x00000010U)))))) 
                              >> 0x00000020U));
    __Vtemp_18[0U] = vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13;
    if ((0U != (3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg))) {
        __Vtemp_18[1U] = (((- (IData)((vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                       >> 0x0000001fU))) 
                           << 0x00000010U) | (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                              >> 0x00000010U));
        __Vtemp_18[2U] = __Vtemp_15[(3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg)];
        __Vtemp_18[3U] = __Vtemp_12[(3U & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg)];
        __Vtemp_18[4U] = (0x0000ffffU & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                         >> 0x00000010U));
    } else {
        __Vtemp_18[1U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                             >> 0x0000000fU)))) 
                           << 0x00000010U) | (0x0000ffffU 
                                              & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13));
        __Vtemp_18[2U] = (((- (IData)((1U & (vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 
                                             >> 7U)))) 
                           << 8U) | (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13));
        __Vtemp_18[3U] = (0x000000ffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13);
        __Vtemp_18[4U] = (0x0000ffffU & vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13);
    }
    __Vtemp_18[5U] = 0U;
    __Vtemp_18[6U] = 0U;
    __Vtemp_18[7U] = 0U;
    if (vlSelfRef.Main__DOT__memory__DOT__bypass_fire) {
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_enable 
            = vlSelfRef.Main__DOT__memory__DOT__bypass_wen;
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_val_0 
            = vlSelfRef.Main__DOT__memory__DOT__bypass_val;
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_address 
            = vlSelfRef.Main__DOT__memory__DOT__bypass_rd;
    } else {
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_enable 
            = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__current_req_wen) 
               & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_io_done));
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_val_0 
            = ((- (IData)((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_io_done))) 
               & (((1U == (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))
                    ? ((1U & ((~ (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0)) 
                              | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write)))
                        ? 0U : __Vtemp_9[(0x07ffffffU 
                                          & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))])
                    : (((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write) 
                        | (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_17))
                        ? 0U : __Vtemp_18[(0x07ffffffU 
                                           & (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op))])) 
                  & (- (IData)((0U != (IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state))))));
        vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_address 
            = ((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__current_req_rd) 
               & (- (IData)((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT___dcache_io_done))));
    }
    vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__lookup_address 
        = (((IData)(vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__io_ready_0) 
            & (IData)(vlSelfRef.Main__DOT__core__DOT__fetch__DOT__io_icache_start_0))
            ? vlSelfRef.Main__DOT___core_io_icache_req_address
            : vlSelfRef.Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_address);
    vlSelfRef.Main__DOT__core__DOT__registers__DOT__w2 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_enable) 
           & (0U != (0x0000001fU & (IData)(vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_address))));
    vlSelfRef.Main__DOT__core__DOT__registers__DOT__same 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_rd) 
           == (IData)(vlSelfRef.Main__DOT__core__DOT___writeback_io_mem_write_address));
    vlSelfRef.Main__DOT__core__DOT__registers__DOT___mask2_T 
        = ((IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__same) 
           & (IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT__w1));
    vlSelfRef.Main__DOT__core__DOT__registers__DOT__mask2 
        = (1U & (~ ((IData)(vlSelfRef.Main__DOT__core__DOT__execute__DOT__bundle_mask) 
                    & (IData)(vlSelfRef.Main__DOT__core__DOT__registers__DOT___mask2_T))));
}

bool VMain___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(VMain___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @( clock)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @( reset)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @( io_execute)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @( io_allocate_warps)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 4U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 4 is active: @( io_warp_count)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 5U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 5 is active: @( io_vga_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 6U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 6 is active: @( io_mem_req_ready)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 7U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 7 is active: @( io_mem_resp)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 8U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 8 is active: @( io_mem_valid)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 9U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 9 is active: @( io_rxd)\n");
    }
    if ((1U & (IData)(triggers[1U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 64 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool VMain___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VMain___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VMain___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clock)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge io_vga_clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VMain___024root___ctor_var_reset_0(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___ctor_var_reset_0\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5452235342940299466ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->io_execute = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3531921623875095080ull);
    vlSelf->io_allocate_warps = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2770525345225329262ull);
    vlSelf->io_warp_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17709542541875654298ull);
    vlSelf->io_complete = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12038341681009738781ull);
    vlSelf->io_vga_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3011363066219644462ull);
    vlSelf->io_hsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9520809520271308995ull);
    vlSelf->io_vsync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4946067916264219785ull);
    vlSelf->io_rgb = VL_SCOPED_RAND_RESET_I(24, __VscopeHash, 5053662448624261142ull);
    vlSelf->io_blanking = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2891825154550602626ull);
    vlSelf->io_mem_req_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17631671499055604328ull);
    vlSelf->io_mem_req_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17267520191236027508ull);
    vlSelf->io_mem_req_bits_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12508716864499667936ull);
    vlSelf->io_mem_req_bits_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15978660601785622488ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->io_mem_req_bits_wdata, __VscopeHash, 16379292280875694977ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->io_mem_resp, __VscopeHash, 4537047121877804218ull);
    vlSelf->io_mem_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7612948073461178717ull);
    vlSelf->io_rxd = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 406838295762192562ull);
    vlSelf->io_txd = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2886118055671713920ull);
    vlSelf->Main__DOT___core_io_icache_req_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3935304976586571435ull);
    vlSelf->Main__DOT___core_io_dcache_req_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16737231331155487057ull);
    vlSelf->Main__DOT___core_io_dcache_req_write_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12827191819331860371ull);
    vlSelf->Main__DOT___core_io_dcache_start = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13904674447902826042ull);
    vlSelf->Main__DOT___core_io_dcache_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 16854240600710545447ull);
    vlSelf->Main__DOT___memory_io_icache_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10914588743016659061ull);
    vlSelf->Main__DOT__memory__DOT___uartTx_io_in_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1659083473256639745ull);
    VL_SCOPED_RAND_RESET_W(256, vlSelf->Main__DOT__memory__DOT___keyTracker_io_keyDown, __VscopeHash, 335858231828430607ull);
    vlSelf->Main__DOT__memory__DOT__bypass_pending = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4215012237601403035ull);
    vlSelf->Main__DOT__memory__DOT__bypass_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 14537518871656080606ull);
    vlSelf->Main__DOT__memory__DOT__bypass_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3318345928285929473ull);
    vlSelf->Main__DOT__memory__DOT__bypass_val = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 92052012854508210ull);
    vlSelf->Main__DOT__memory__DOT__is_keytracker = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1443039256063092000ull);
    vlSelf->Main__DOT__memory__DOT__is_excep = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7474426316675614893ull);
    vlSelf->Main__DOT__memory__DOT__bypass_fire = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10839639330722216575ull);
    vlSelf->Main__DOT__memory__DOT__uartTx_io_in_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12710021629813096122ull);
    vlSelf->Main__DOT__memory__DOT____Vcellinp__mem__io_dcache_start = 0;
    vlSelf->Main__DOT__memory__DOT____Vcellinp__uartTx__io_in_bits = 0;
    vlSelf->Main__DOT__memory__DOT__mem__DOT___l2_cache_io_mem_valid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11193949715652966463ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT___dcache_queue_io_dcache_req_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13139385046243979505ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16207274341321101233ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT___arbiter_io_resp_to_cache_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 760656762144629407ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT___dcache_io_done = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10594841956098799392ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT____Vcellinp__arbiter__io_cache_req_0_valid = 0;
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___data_array_ext_R0_data, __VscopeHash, 7045609875900518993ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___meta_array_ext_R0_data = VL_SCOPED_RAND_RESET_I(20, __VscopeHash, 8704415137547368291ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4963869301519973019ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16650289296315394402ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18239256985575494984ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_op = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11152435512905617723ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17900120889686964451ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8308936532972199553ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__lookup_address_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15455682064546451038ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__read_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3676563393101351160ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__wb_data_reg, __VscopeHash, 5956021130287464070ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__wb_addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8914250311619779322ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__valid_cleared = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5069518690433153185ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14049652291599324601ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16563700560044233433ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__updated_word = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6164824953844195795ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17541246649814959968ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_13 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6773946688252307441ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__updated_word_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16636665620721244408ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT___GEN_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8593159116802957228ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT____Vcellinp__meta_array_ext__W0_en = 0;
    VL_SCOPED_RAND_RESET_ASSIGN_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT____Vxrand___0, __VscopeHash, 17290050618109357377ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory[__Vi0], __VscopeHash, 1527319275109251601ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6931572419120767278ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7396017324364071859ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(20, __VscopeHash, 5322046975869798533ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(20, __VscopeHash, 15335813290832523936ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7265073541928946912ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13873288512712696644ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__io_ready_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13336520138945642802ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT___meta_array_ext_R0_data = VL_SCOPED_RAND_RESET_I(20, __VscopeHash, 17562820208319318577ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16610453321853317835ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13267045554318309200ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_read = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7367134717540012388ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5807947708492201073ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__lookup_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3279729852400464486ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__word_offset_REG = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10702962357203672593ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__cache_tag_REG = VL_SCOPED_RAND_RESET_I(18, __VscopeHash, 11813239588205703804ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__line_addr_REG = VL_SCOPED_RAND_RESET_I(26, __VscopeHash, 7117941885514665021ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__read_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13624475298516954288ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3561770912321615070ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 918572508830547531ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT___GEN_5, __VscopeHash, 15281730230936990262ull);
    VL_SCOPED_RAND_RESET_ASSIGN_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT____Vxrand___0, __VscopeHash, 15155160836590947430ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT__Memory[__Vi0], __VscopeHash, 2979539439325332815ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12158611584624242155ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13597321621169499399ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(20, __VscopeHash, 15285208608660994051ull);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(20, __VscopeHash, 17252979484570091919ull);
    }
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___data_array_ext_R0_data, __VscopeHash, 18157268614147336268ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___meta_array_ext_R0_data = VL_SCOPED_RAND_RESET_I(18, __VscopeHash, 10944657972349398984ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13482588446044449927ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15493596356784413005ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14991980076282670387ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_wdata, __VscopeHash, 2252102554756107625ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__lookup_address = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1448833845416245084ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__lookup_address_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9115591370832548150ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__read_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16881089212534182630ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_data_reg, __VscopeHash, 12951019448787545874ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__wb_addr_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18380060726920301468ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__hit = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8972886911648869341ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_req_accepted = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4502392404011933953ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__mem_ack = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1956360690524788713ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10404935194664380751ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5499502480822453090ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT___GEN_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4427680686995031358ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT____Vcellinp__meta_array_ext__W0_en = 0;
    VL_SCOPED_RAND_RESET_ASSIGN_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT____Vxrand___0, __VscopeHash, 9926916400133942391ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory[__Vi0], __VscopeHash, 13999094651378927264ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 13716135133914669254ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(18, __VscopeHash, 15443980346376594597ull);
    for (int __Vi0 = 0; __Vi0 < 1024; ++__Vi0) {
        vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(18, __VscopeHash, 17878804730252980255ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10450055561626630613ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__current_req_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 583176547889391229ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__current_req_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8676108416228328322ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__io_dcache_start_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 592851719631062448ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__enq_ptr_value = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 4078590926807804099ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__deq_ptr_value = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 4997372216587430366ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__maybe_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17729511569092174947ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ptr_match = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15107913729169879753ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11704349289917098161ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5878666478753509938ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__io_deq_valid_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10307604394276402760ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__do_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17584191669293192418ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(76, vlSelf->Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory[__Vi0], __VscopeHash, 8441162357258404239ull);
    }
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12008475684131438002ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__owner = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10449814361798878998ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__mem_req_accepted = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15231885308083027036ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__latched_req_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 329623345653618642ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__latched_req_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11319665443673621191ull);
    VL_SCOPED_RAND_RESET_W(512, vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__latched_req_wdata, __VscopeHash, 5109669152938407969ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__io_mem_req_valid_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1621594389485898122ull);
    vlSelf->Main__DOT__memory__DOT__mem__DOT__arbiter__DOT___io_resp_to_cache_1_T = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13351843122869532008ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__enq_ptr_value = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 8958746294601730742ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__deq_ptr_value = VL_SCOPED_RAND_RESET_I(11, __VscopeHash, 18059093182302719230ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__maybe_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7512761930901353055ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ptr_match = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15729964894959302831ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3954192493613811700ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__io_deq_valid_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11216223235479304824ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__do_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3307861499206644269ull);
    for (int __Vi0 = 0; __Vi0 < 2048; ++__Vi0) {
        vlSelf->Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ram_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8823066270056497526ull);
    }
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__counter = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16532045439482904982ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__bitIdx = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7561174638802865367ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__shiftReg = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 6141581151096634472ull);
    vlSelf->Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__busy = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15744725645773516681ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8880685154763630255ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7505625887400733923ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10073460652000764886ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4075035788580686960ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2030760768724139573ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 715319396149318670ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7531602738153265424ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12067823455819701506ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 266089951454619855ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12755403021502870471ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 505343459355672472ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1346965279743031163ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5813037898082250928ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_13 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16128977864171431880ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11896400134813043372ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13830154863614367941ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14520904814856236014ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6307688785885929072ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2093835031579841878ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_19 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10954492691991607434ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_20 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 410216236307643491ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5822088291080360222ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2824698061706051882ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 376880361469650761ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_24 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13187218683634496774ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2205573909905370800ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2879007592269603920ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7493125015028891588ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_28 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1762074247822230716ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1921996280523077185ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_30 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1866839021355193066ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_31 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6689070959007492194ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_32 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12397151761821311207ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_33 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3645855949679589134ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_34 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7889289688319483318ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_35 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10654018338773672512ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_36 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8104839552476333552ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_37 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12098324059601672600ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_38 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3483284226450788758ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_39 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 350056109482722608ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_40 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14458446537156549866ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_41 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4008803215315114556ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_42 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14861931853454206577ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_43 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4830284690037853907ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_44 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16111057235818254807ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 615776117504395830ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_46 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11816363233061227454ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_47 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 598296999538729712ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_48 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3193665414989582158ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_49 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9249282563332145847ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_50 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2130423052529701008ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_51 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10832476981133116421ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_52 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8939800524572913927ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_53 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2633364671569743158ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_54 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2376096242053922171ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_55 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7823661339162891789ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_56 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5220271525958033270ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_57 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17989058122221217990ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_58 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8185337567183627774ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_59 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2299866148443777052ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_60 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9210988984369265734ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_61 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2855925912600910167ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_62 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10576027999947673778ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_63 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2021290613730931652ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_64 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 898556935919978007ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_65 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12551603354196918260ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_66 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10150567875975634081ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_67 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5409390841693124326ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_68 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2250917017378173432ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_69 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14678182256394645184ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_70 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12982634304134417598ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_71 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16618765323054931847ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_72 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6983655671506421514ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_73 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17053985791072899693ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_74 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 292163515430822222ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_75 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 323732261629816268ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_76 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12710066983889282496ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_77 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6847919844001832820ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_78 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4466421015348530261ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_79 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17027093096718569226ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_80 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14389348612163034442ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_81 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6964981819196949660ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_82 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14253729369856956633ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_83 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17753485270585751445ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14439947513681538400ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_85 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13709454670203150625ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_86 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2170391907413189902ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_87 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17147758214134153590ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_88 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14422123064425046692ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_89 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15249821093605540484ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_90 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8628365657590420739ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_91 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3141913050217347035ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_92 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11963760634539908550ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_93 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14741070149394339073ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_94 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18005174557389081389ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_95 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10698064324443730816ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_96 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17144812116773465893ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_97 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6648909278405610083ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_98 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11825477610532452584ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_99 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11227083843255628849ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_100 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11427901004849529155ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_101 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7477494477778517628ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_102 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12365376300333054287ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_103 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12952601860102181693ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_104 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5097187501308935225ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_105 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7483725637353219104ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_106 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9014139171628247562ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_107 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12614519758359457665ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_108 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1974809363194374990ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_109 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11717979050009260377ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_110 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5699407968886371732ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_111 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5172413217737544939ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_112 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15763742932653957751ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_113 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1572821839325975910ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_114 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9059997361295345202ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_115 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4018942063729404740ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_116 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8798472722272731096ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_117 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15533081575490138287ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_118 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4549057919007453425ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_119 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1868189007449788979ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_120 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 712621088081057518ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_121 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2192629226268001783ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_122 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12958995946045057472ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_123 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2135049110606154928ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_124 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10767861943839316424ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_125 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4987291253092244001ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_126 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6914355896495125656ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_127 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11638427603098876955ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_128 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13899592345658047485ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_129 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 61465707824757294ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_130 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8127043618432064328ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_131 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1253456454951487958ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_132 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14023115435019130520ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_133 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3771598498281384921ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_134 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10058289947825328567ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_135 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14184876077385710283ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_136 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11005978405470454811ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_137 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2618127344273138798ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_138 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8254995368963500663ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_139 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1781911154768780394ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_140 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9472981154951363877ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_141 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5474830973434640543ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_142 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15620741149344954142ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_143 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16440677539862390295ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_144 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4219558043644119028ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_145 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7877895446982445131ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_146 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 534586468044527353ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_147 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 943806747114475392ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_148 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2536771291361220286ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_149 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5306177956439574859ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_150 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4821778511221450905ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_151 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2815788702859718472ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_152 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17089498418482584647ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_153 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17648134042631444931ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_154 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3668307357213274954ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_155 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16751593334281249327ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_156 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2771766648863069582ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_157 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5684510327736517361ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_158 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7443782852601774272ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_159 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4443656358068706920ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_160 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3127541206485442547ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_161 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3376531836220710679ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_162 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6644449290005904815ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_163 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2430480344785827566ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_164 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1784190531435734938ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_165 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 25294707515778258ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_166 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18159849067031330028ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_167 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2640691188375979811ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_168 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6578292978392686361ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_169 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6501912533214049240ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_170 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18175020992381243547ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_171 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13817715033366143905ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_172 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8283966953519326372ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_173 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11626581031160169087ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_174 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9986719944583828256ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_175 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5868521298975100272ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_176 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13161965459745069031ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_177 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1488809708801791295ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_178 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3270911420883208664ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_179 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13840425675331615509ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_180 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11050424818586708329ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_181 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17846842328569014858ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_182 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14743111691680092419ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_183 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1406877271540855446ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_184 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17860400390234231175ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_185 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3195010459793375437ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_186 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15349973644398386568ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_187 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11136004699178275405ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_188 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13005112525974063913ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_189 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7220689995069203019ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_190 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4471096949592622968ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_191 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12853552914647381509ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_192 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13290349402589129097ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_193 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11512476231610820758ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_194 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6671984028418639233ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_195 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17408548048197962954ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_196 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8686749716135477266ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_197 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 963988797805146701ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_198 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14161857098459347677ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_199 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10464622887113756961ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_200 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9968133003701958630ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_201 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 849460412911530373ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_202 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1925442961712972278ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_203 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9737236156705660355ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_204 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4724463692069146381ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_205 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14113955359069710020ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_206 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1213256515832961017ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_207 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15798755778508166195ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_208 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5245662456879552023ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_209 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9933440547547456189ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_210 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6198439840141747650ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_211 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8733156444916615106ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_212 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8720716714349239566ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_213 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9644127084793329122ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_214 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13957741558698756892ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_215 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13616208506994042904ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_216 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14524398937257805639ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_217 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5994482899268443983ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_218 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 49736285749078379ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_219 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6905453539145121405ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_220 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17759462317001912955ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_221 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15232921095262256617ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_222 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6803239387819694466ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_223 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9480480331873823208ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_224 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13794094805779252778ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_225 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12338341443156834929ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_226 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8992888529052149114ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_227 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1509800337073235274ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_228 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12869199651641693160ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_229 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 557811725467171497ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_230 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4510256240775539464ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_231 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8529834133131072352ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_232 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12675656488498766365ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_233 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13661617868914743478ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_234 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2687560113022859501ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_235 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11761716927009303591ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_236 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1016518161707786137ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_237 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18305597778240406717ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_238 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4004676059898616306ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_239 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3470295211314074547ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_240 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7975364510145291733ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_241 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17024253544873368198ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_242 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 712794679917933542ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_243 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 40695786335011930ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_244 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3469478623709023387ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_245 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15196362650156282029ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_246 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17331647858910548637ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_247 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7933792819928965438ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_248 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7385888269999488969ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_249 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6598335105689260391ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_250 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11667968207753907933ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_251 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2529788017614400102ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_252 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15599196981308595547ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_253 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11868248957182199454ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_254 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15543525205398458124ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__keyState_255 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3714168585539966198ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__lastCodeReg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9623783796323582216ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__lastPressedReg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10645523885196721311ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__eventValidReg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 482578930249277835ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__state = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10959091309821322037ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__eventType = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13382416350321168829ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__counter = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17534027059000100619ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__bitIdx = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10797124445052368277ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__shiftReg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17334625813414675767ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__dataReg = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11215105109039680567ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__validReg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14063947397438612791ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9665910726143626705ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__rxSync_REG = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1492206147117039334ull);
    vlSelf->Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__rxSync = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2544669883911075140ull);
    vlSelf->Main__DOT__memory__DOT__hardwareTimer__DOT__cycleCounter = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10654948482990637761ull);
    vlSelf->Main__DOT__memory__DOT__hardwareTimer__DOT__microsReg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13986576412865442496ull);
    vlSelf->Main__DOT__core__DOT___writeback_io_mem_write_enable = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15264526684167721351ull);
    vlSelf->Main__DOT__core__DOT___writeback_io_mem_write_address = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 12625800531360664967ull);
    vlSelf->Main__DOT__core__DOT___writeback_io_mem_write_val_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10323883159107084318ull);
    vlSelf->Main__DOT__core__DOT___execute_io_next_instruction_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17838653109435216447ull);
    vlSelf->Main__DOT__core__DOT___execute_io_pc_redirect_bits = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5847425602422489404ull);
    vlSelf->Main__DOT__core__DOT___execute_io_lsu_req_bits_base_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3040860799647587899ull);
    vlSelf->Main__DOT__core__DOT___execute_io_lsu_req_bits_wdata_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10129617504260108650ull);
    vlSelf->Main__DOT__core__DOT___execute_io_lsu_req_bits_mask = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8199569123150726630ull);
    vlSelf->Main__DOT__core__DOT___execute_io_memory_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9344236958272925477ull);
    vlSelf->Main__DOT__core__DOT___execute_io_jump_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9597274260298414545ull);
    vlSelf->Main__DOT__core__DOT___execute_io_mem_issue = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8685764530848690638ull);
    vlSelf->Main__DOT__core__DOT___execute_io_mem_issue_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17547286900592025069ull);
    vlSelf->Main__DOT__core__DOT___execute_io_warp_terminate = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16515819149142577870ull);
    vlSelf->Main__DOT__core__DOT___execute_io_mark_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7833035142004343791ull);
    vlSelf->Main__DOT__core__DOT___execute_io_mark_warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6333513470605457028ull);
    vlSelf->Main__DOT__core__DOT___execute_io_spawn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2347012892818017029ull);
    vlSelf->Main__DOT__core__DOT___execute_io_barrier = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7152039167748830948ull);
    vlSelf->Main__DOT__core__DOT___warp_scheduler_io_warp_swap_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5364763763906514675ull);
    vlSelf->Main__DOT__core__DOT___warp_scheduler_io_allocate_warp = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2473194855051323340ull);
    vlSelf->Main__DOT__core__DOT___warp_scheduler_io_allocate_id = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14198968522589113002ull);
    vlSelf->Main__DOT__core__DOT___warp_scheduler_io_allocate_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10339548940044789253ull);
    vlSelf->Main__DOT__core__DOT__fetch_stall = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14735562016094349391ull);
    vlSelf->Main__DOT__core__DOT__read_io_flush = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3386830018469287390ull);
    vlSelf->Main__DOT__core__DOT__execute_io_flush_REG = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12507663912585600716ull);
    vlSelf->Main__DOT__core__DOT____Vcellinp__fetch__io_fetch_request_fetch_op = 0;
    VL_ZERO_RESET_W(128, vlSelf->Main__DOT__core__DOT____Vcellinp__read__io_rum);
    vlSelf->Main__DOT__core__DOT____Vcellinp__writeback__io_mem_issue_count = 0;
    vlSelf->Main__DOT__core__DOT__execute__DOT__bundle_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 4385935714553691589ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__bundle_rd_val_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11497590467547207685ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__bundle_mask = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13606874980495410515ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__bundle_rd_wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1456268798931670355ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__bundle_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 703634024911400869ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13703073171274398880ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__lmask_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15149061912446404568ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__lmask_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 938925457511343755ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__lmask_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13575220175468975858ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__lmask_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10053032216006209846ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1258973570993523953ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18389240403638326894ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___pc_plus_imm_T = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 971477620594528088ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7567468946842156667ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__isM = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7551879015080628960ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15811755695257509498ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0_io_b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12811095981224773301ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11441226094190162352ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8704799287479779097ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 501354910283697889ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7621068030683041194ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__take_branch = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1008084027174162661ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__target = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4324864193288634027ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__target_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14179263854291817613ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14355411014557186297ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1589813450847322332ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12593765815300731127ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17777011279935235246ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3603027229823328971ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17330703850231733320ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT___GEN_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1719706357366163949ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__io_mark_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18367003700798230376ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT____Vcellinp__malus_0__io_start = 0;
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT____Vcellinp__div__io_start = 0;
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2034641780235554676ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__func3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7786109369349952824ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__a = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12018529277568876440ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__b = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16732827843958690063ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__divNeg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13768159278783536270ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__outNeg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14407538547955123355ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__counter = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 3136414509934435003ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__r = VL_SCOPED_RAND_RESET_Q(33, __VscopeHash, 4070743115700345790ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__divByZeroCase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16852232456549310687ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__overflowCase = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10209213426503312050ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__orga = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2586841079292015807ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__isDivOp = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16861145100421814989ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT___GEN_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2367667721849755612ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_29 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4995880572198638422ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_39 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2484452517126890583ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_49 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10625186928020232047ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0__DOT___i_alu_T_69 = VL_SCOPED_RAND_RESET_I(31, __VscopeHash, 9668321700824218337ull);
    vlSelf->Main__DOT__core__DOT__execute__DOT__alus_0__DOT___GEN_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3018295413028960607ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9552313188358138455ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10575637936312859786ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15396832116356234403ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13358586719500092751ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_4 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3191275953779791351ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15946797240062622347ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_6 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11738598290268602798ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_7 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14806527309646844381ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_8 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18271478624189046269ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15030734764697731378ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_10 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14690248949851307943ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_11 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6428879155776413945ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_12 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17337653706914066146ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_13 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7146674549656000012ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_14 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5422059111179875489ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_15 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6258217265056578025ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_16 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4985559059356978506ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_17 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10001677660494837091ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_18 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14410380513147577027ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_19 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6471236577886582687ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_20 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13415554175464362461ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_21 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6466871457984013515ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_22 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6737243457388432965ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_23 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13507051421023720521ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_24 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17716085792305912329ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_25 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10168433359863045913ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_26 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16390973153597383383ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_27 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14022047208606171432ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_28 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5845457038119672246ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_29 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4071790179045865550ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_30 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5952729509441223850ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_31 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8408852032087436553ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_32 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 237456628565246559ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_33 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4199997589005311530ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_34 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6396091950780652093ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_35 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5581752299861556858ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_36 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9233764701568496312ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_37 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5588304084805842007ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_38 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 576758039057232973ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_39 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 116379398672078736ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_40 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6321711855359422884ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_41 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9394297302107219017ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_42 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15726672397772061148ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_43 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7523400631417080913ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_44 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4692728493320223065ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_45 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14036915689140589932ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_46 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18273373441003725931ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_47 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12847930907053041834ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_48 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10397017242544659078ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_49 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 303857935762196053ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_50 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10435448271694217825ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_51 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8862333458310488143ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_52 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9106625003940665746ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_53 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10312293308589729734ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_54 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15753688115130155226ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_55 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17045514130828697946ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_56 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12730369177834667466ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_57 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15969863178800789644ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_58 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17425735523337277906ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_59 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9367285477191255016ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_60 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8123361299596772228ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_61 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9412360250569776794ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_62 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17437923249624398934ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_63 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6788625537586030197ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_64 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10311648918536956742ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_65 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5508535539055649683ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_66 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16105544655111592236ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_67 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18009663603379730419ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_68 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16546065940552029624ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_69 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13651959228163736861ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_70 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6144950224823102627ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_71 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14287769783898535416ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_72 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8680611340203662460ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_73 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1845474553699085878ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_74 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9986809974855363961ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_75 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5640531012235325655ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_76 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4476824544146831829ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_77 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10972256353872064645ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_78 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6621983771486878342ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_79 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11187806218028919619ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_80 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13848300347240841769ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_81 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15905722209894548908ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_82 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9624497337519924539ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_83 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10900137910231143828ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_84 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 279147143093165148ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_85 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12523261586274379991ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_86 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2257715967589424431ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_87 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8714309518878417963ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_88 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17127335240331762651ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_89 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13875556888364431520ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_90 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17539305200673260880ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_91 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17590289586936705941ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_92 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4616215540506176959ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_93 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3361050543945844147ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_94 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16138438476017661511ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_95 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11507570197325984482ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_96 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7639753123089440568ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_97 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5841489948160377260ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_98 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4153486276994389621ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_99 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2183720354482519089ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_100 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14751035201415966237ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_101 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8603098189480792588ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_102 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7341771040377327177ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_103 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4547308696956765659ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_104 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8265865291737172798ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_105 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16876214021521067981ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_106 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13722595900602215800ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_107 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6250521773562624514ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_108 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9529737160620940515ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_109 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2936380609679926742ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_110 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3002783896473004110ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_111 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9788764371639483480ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_112 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11800125887227428891ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_113 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2714200883356579911ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_114 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16053522693079382628ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_115 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8146736712336899412ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_116 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15937102196490853247ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_117 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11859849909753351182ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_118 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13655652986495751781ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_119 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8399261676630101083ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_120 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11902435117606934624ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_121 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4522597032900610175ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_122 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9417064050113351308ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_123 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16708682532673339253ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_124 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3299225300968042550ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_125 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15350089974635459811ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_126 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1087664974439172349ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__lvt_127 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14393224747439565662ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__w1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10262747312803574412ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__w2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7102206076117317656ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__same = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8918388906188350626ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT___mask2_T = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8927990134035565311ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__mask2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16150474682134798399ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__sel_a = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4782042361104137538ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__sel_b = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1421784616189598554ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__a_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11939592099599902269ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__b_x0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13329934253868593234ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT____Vxrand___1 = VL_SCOPED_RAND_RESET_ASSIGN_I(32, __VscopeHash, 8226460345754921847ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(32, __VscopeHash, 5059277597740778087ull);
    for (int __Vi0 = 0; __Vi0 < 128; ++__Vi0) {
        vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 196341566371129422ull);
    }
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1268789587747934931ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 1800210511108083882ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R1_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13043168948302252621ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT___R1_addr_d0 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10585587665872380183ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT____Vxrand___1 = VL_SCOPED_RAND_RESET_ASSIGN_I(32, __VscopeHash, 7611546782160636377ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(32, __VscopeHash, 4837233624425656677ull);
    for (int __Vi0 = 0; __Vi0 < 128; ++__Vi0) {
        vlSelf->Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 22915609514449197ull);
    }
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT___R1_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18193170894125287200ull);
    vlSelf->Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT___R1_addr_d0 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10578261538499776744ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT___q_q_io_deq_bits_func3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6671268453983254030ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT___q_q_io_deq_bits_write = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5662705886355949995ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__lane = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 717108533955628332ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8849680404597034133ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__enq_ptr_value = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1705317518277999090ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1556820569150844505ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__maybe_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14972954513483672634ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ptr_match = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 828354275537739801ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10198255289230108870ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14101567682109647816ull);
    vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__do_enq = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13948494283388264895ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(108, vlSelf->Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory[__Vi0], __VscopeHash, 11483282124407840400ull);
    }
    vlSelf->Main__DOT__core__DOT__decode__DOT__rs1 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 15120192593514529076ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__rs2 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 13295063167014064209ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 3640641626874041609ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__immediate = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8620331560352148696ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 2294557751924411103ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__func3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13166064456402180345ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__func7 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 7394732787740265944ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6462560037534632105ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8232783593212121378ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 877384696876131503ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10477283511743842992ull);
    vlSelf->Main__DOT__core__DOT__decode__DOT__decoder__DOT__format = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11513695895723827540ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_0 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5744365110433580528ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_1 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14573526793391660680ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_2 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14093962465957982311ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_3 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2038128699642343541ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_4 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8716022533244766596ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_5 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10191132468587258773ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_6 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4143470591551573351ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_7 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11851874269820884325ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_8 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10352764853204411051ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_9 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3817956445448209445ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_10 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16543583841148540237ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_11 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14943045647183810096ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_12 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3661495587542064926ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_13 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6985769212096442119ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_14 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8816727968745654761ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_15 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2777296263390315977ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_16 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17345946757700164199ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_17 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3144848822583078515ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_18 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8246269752797699415ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_19 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10481378744776406321ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_20 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6241655864624635649ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_21 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8739761861807171228ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_22 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12788927442585571015ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_23 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5239932083336355011ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_24 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12653124281710313521ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_25 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16481339674822864977ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_26 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1944346898058151549ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_27 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8273470727164845991ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_28 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17015288183549752301ull);
}

VL_ATTR_COLD void VMain___024root___ctor_var_reset_1(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___ctor_var_reset_1\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_29 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4226499464796272491ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_30 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 330515211766211588ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_31 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5158839571875779138ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_32 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9537405007987650053ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_33 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6085816963537163421ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_34 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13452961746300871809ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_35 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2594665955050041680ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_36 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9745794966798582254ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_37 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6661808733368757397ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_38 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6012497479263140078ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_39 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 174783806142563353ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_40 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14697740426314038890ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_41 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2532835889752506234ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_42 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9138357809781009138ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_43 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10139198026749742471ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_44 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4280626849166238727ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_45 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7026957656680780222ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_46 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7705367460721621728ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_47 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17591769270591264925ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_48 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18136792867823470945ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_49 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18335708461246625368ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_50 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4831751958590618366ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_51 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5462163299812972241ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_52 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 378284830565560900ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_53 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10856694459794222229ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_54 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13205518776208412002ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_55 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15260678987081822680ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_56 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11996574579086894370ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_57 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12311262594611877899ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_58 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16061264240253929650ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_59 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2127721774556106054ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_60 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 158316940318144798ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_61 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10287218541264805074ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_62 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5728626889872536260ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_63 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2859575855826501825ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_64 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6745245995602611756ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_65 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 523320866641533040ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_66 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3202761279192393249ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_67 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 919498522109020965ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_68 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3211143535777316668ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_69 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16191027013945154707ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_70 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8210993824378053563ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_71 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10516640497364089651ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_72 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6107499920199820076ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_73 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9935149900367261964ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_74 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6498114403069919914ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_75 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10324633557347177866ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_76 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16984790137620999831ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_77 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18267710757310167499ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_78 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13878840199751947415ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_79 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6386458730303435399ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_80 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18328992360300815060ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_81 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16864829284528120541ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_82 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12628357441491551761ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_83 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13823812583979110192ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_84 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12509658448577547317ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_85 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17163971147752814907ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_86 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15754909641514444784ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_87 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16470559968812312114ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_88 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11201522857890973711ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_89 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2040549800907698805ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_90 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5709629764915510544ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_91 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15321655420875167948ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_92 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10792183388899068124ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_93 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17216865416700520537ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_94 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1951121296751840743ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_95 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12864277940337985515ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_96 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13017188825607418559ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_97 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6684862981770631162ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_98 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 422007336052444746ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_99 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10535925209705759823ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_100 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14084480683782605838ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_101 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2927234651965316224ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_102 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12508466678872002547ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_103 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3055505276925413312ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_104 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5941202276163432973ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_105 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12405098103628828987ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_106 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15978467171379014807ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_107 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6120867989269033508ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_108 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 88304755682356079ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_109 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8677449647281871905ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_110 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5842498347425099822ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_111 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11761811858602614756ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_112 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14228028561496348037ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_113 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7979267694098339147ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_114 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11213907308673120387ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_115 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13344539774491660283ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_116 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15198781696190195926ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_117 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18434905448684245811ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_118 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11508817283472864302ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_119 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2069567571816853587ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_120 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2898718002864006368ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_121 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11669190331524558056ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_122 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1601108932282870679ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_123 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10621608360569043903ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_124 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16191979256409727015ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_125 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11366483120743488360ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_126 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2612891087389799705ull);
    vlSelf->Main__DOT__core__DOT__writeback__DOT__mem_pending_127 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14553425935985408649ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__raw_hazard = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7920297160597282698ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_rd = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 17351677517330255214ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_immediate = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5550502415461629578ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_opcode = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 10439889735513000629ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_func3 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 7252477524957699172ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_func7 = VL_SCOPED_RAND_RESET_I(7, __VscopeHash, 18136124994006173870ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1143738755152148300ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__bundle_warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15171656173754329168ull);
    vlSelf->Main__DOT__core__DOT__read__DOT__valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2208261859696784492ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4613287801882979442ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5295577628428660069ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9998630575134943403ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__speculative_instruction_pointers_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 451537722559355100ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__instruction_pointers_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15573845272724539535ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__instruction_pointers_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2681929785547089922ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__instruction_pointers_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8233966468007941543ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__instruction_pointers_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17911576199055148378ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__ignore_instruction = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13255985564535965716ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__request_instruction_pointer = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15337620096633146186ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__request_warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13064171434608329955ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__request_in_flight = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1549086032122066858ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__fetch_result_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12635217822130948819ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__fetch_result_warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5036595355154559380ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__fetch_result_inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4305705841525906880ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__fetch_result_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17760940615811882104ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->Main__DOT__core__DOT__fetch__DOT___GEN, __VscopeHash, 2395191199989259613ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__dequeuing = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9540822295304865982ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__redirecting = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14558117267155363937ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__can_issue = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7422640874595158869ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9606526483910126942ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT___GEN_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1545737795653936780ull);
    vlSelf->Main__DOT__core__DOT__fetch__DOT__io_icache_start_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12142577825724599083ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__active_warp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10862706124050926185ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__warp_ids_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7033218042301895175ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__warp_ids_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10411406771588146093ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__warp_ids_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7633931496986953626ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__warp_ids_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5010406488204168914ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2989495370754290717ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4524172307858531476ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17992869865983763943ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 527032026361307970ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__warp_count = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5070465208745472333ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__next_warp = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15193962725683324130ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__spawn_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11285347382077636758ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3023301770678461845ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14313248612014715364ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 529659290488535208ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10534801798298147466ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_count = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 1570929737064771575ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT__barrier_target = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17638759304847386457ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16692483501027943244ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___slot_T_5 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17970109552886900834ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9505843535827067263ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9990043728400881945ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17250883103841132194ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_3 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12025486182965961620ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_4 = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3313773164167556249ull);
    vlSelf->Main__DOT__core__DOT__warp_scheduler__DOT___GEN_5 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6522369076099791134ull);
    vlSelf->Main__DOT__vga_controller__DOT__hCount = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 4739985356284885954ull);
    vlSelf->Main__DOT__vga_controller__DOT__vCount = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 3372885813164024586ull);
    vlSelf->Main__DOT__vga_controller__DOT__active = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4572401688804916495ull);
    vlSelf->Main__DOT__vga_controller__DOT___vCountMult_T_2 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 7698004267426281225ull);
    vlSelf->Main__DOT__vga_controller__DOT__memory_ext__DOT____Vxrand___1 = VL_SCOPED_RAND_RESET_ASSIGN_I(12, __VscopeHash, 7076433040312139822ull);
    vlSelf->Main__DOT__vga_controller__DOT__memory_ext__DOT____Vxrand___0 = VL_SCOPED_RAND_RESET_ASSIGN_I(12, __VscopeHash, 12463391787573121389ull);
    for (int __Vi0 = 0; __Vi0 < 76800; ++__Vi0) {
        vlSelf->Main__DOT__vga_controller__DOT__memory_ext__DOT__Memory[__Vi0] = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 3903301749656706419ull);
    }
    vlSelf->Main__DOT__vga_controller__DOT__memory_ext__DOT___R0_en_d0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15480179119022734717ull);
    vlSelf->Main__DOT__vga_controller__DOT__memory_ext__DOT___R0_addr_d0 = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 5867723270892041933ull);
    vlSelf->__VdfgRegularize_h6e95ff9d_0_0 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_3 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_4 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_5 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_6 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_8 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_10 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_13 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_14 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_15 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_16 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_19 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_20 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_21 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_22 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_23 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_26 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_27 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_28 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_30 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_31 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_32 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_33 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_34 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_36 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_40 = 0;
    vlSelf->__VdfgRegularize_h6e95ff9d_0_41 = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__bypass_pending = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__current_mem_req_address = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__valid_cleared = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__icache__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_read = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__icache__DOT__current_mem_req_write = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_addr = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__current_mem_req_write = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__enq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__deq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__busy = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__mem__DOT__arbiter__DOT__mem_req_accepted = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__enq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__deq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__counter = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__bitIdx = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__shiftReg = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__uartTx__DOT__uartTx__DOT__busy = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__eventType = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__counter = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__bitIdx = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__shiftReg = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__keyTracker__DOT__uart__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__hardwareTimer__DOT__cycleCounter = 0;
    vlSelf->__Vdly__Main__DOT__memory__DOT__hardwareTimer__DOT__microsReg = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__lmask_0 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__lmask_1 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__lmask_2 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__lmask_3 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__state = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__a = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__b = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__counter = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__execute__DOT__malus_0__DOT__div__DOT__r = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_0 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_1 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_2 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_3 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_4 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_5 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_6 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_7 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_8 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_9 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_10 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_11 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_12 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_13 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_14 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_15 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_16 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_17 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_18 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_19 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_20 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_21 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_22 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_23 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_24 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_25 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_26 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_27 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_28 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_29 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_30 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_31 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_32 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_33 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_34 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_35 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_36 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_37 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_38 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_39 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_40 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_41 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_42 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_43 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_44 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_45 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_46 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_47 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_48 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_49 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_50 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_51 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_52 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_53 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_54 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_55 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_56 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_57 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_58 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_59 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_60 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_61 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_62 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_63 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_64 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_65 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_66 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_67 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_68 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_69 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_70 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_71 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_72 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_73 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_74 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_75 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_76 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_77 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_78 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_79 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_80 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_81 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_82 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_83 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_84 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_85 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_86 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_87 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_88 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_89 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_90 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_91 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_92 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_93 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_94 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_95 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_96 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_97 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_98 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_99 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_100 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_101 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_102 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_103 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_104 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_105 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_106 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_107 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_108 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_109 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_110 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_111 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_112 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_113 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_114 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_115 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_116 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_117 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_118 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_119 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_120 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_121 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_122 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_123 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_124 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_125 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_126 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__registers__DOT__lvt_127 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__lsu__DOT__lane = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__lsu__DOT__q_q__DOT__enq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__lsu__DOT__q_q__DOT__deq_ptr_value = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__decode__DOT__valid = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_125 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_124 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_123 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_122 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_121 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_120 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_119 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_118 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_117 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_116 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_115 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_114 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_113 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_112 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_111 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_110 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_109 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_108 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_107 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_106 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_105 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_104 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_103 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_102 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_101 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_100 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_99 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_98 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_97 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_96 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_95 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_94 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_93 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_92 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_91 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_90 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_89 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_88 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_87 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_86 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_85 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_83 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_82 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_81 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_80 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_79 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_78 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_77 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_76 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_75 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_74 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_73 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_72 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_71 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_70 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_69 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_68 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_67 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_66 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_65 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_64 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_63 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_62 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_61 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_60 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_59 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_58 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_27 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_26 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_25 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_24 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_23 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_22 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_21 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_20 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_19 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_84 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_18 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_17 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_16 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_15 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_14 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_13 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_12 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_8 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_0 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_1 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_2 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_3 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_4 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_5 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_6 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_7 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_9 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_10 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_11 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_28 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_29 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_30 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_31 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_32 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_33 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_34 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_35 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_36 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_37 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_38 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_39 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_40 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_41 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_42 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_43 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_44 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_45 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_46 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_47 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_48 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_49 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_50 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_51 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_52 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_53 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_54 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_55 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_56 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_57 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_126 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__writeback__DOT__mem_pending_127 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__read__DOT__valid = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__fetch__DOT__ignore_instruction = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__fetch__DOT__request_in_flight = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__fetch__DOT__fetch_result_valid = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__active_warp = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_0 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_1 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_2 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__active_warps_3 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__next_warp = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_0 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_1 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_2 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_waiting_3 = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_count = 0;
    vlSelf->__Vdly__Main__DOT__core__DOT__warp_scheduler__DOT__barrier_target = 0;
    VL_ZERO_RESET_W(512, vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory__v0);
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__dcache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    VL_ZERO_RESET_W(512, vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT__Memory__v0);
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__icache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__icache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    VL_ZERO_RESET_W(512, vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory__v0);
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__data_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__l2_cache__DOT__meta_array_ext__DOT__Memory__v0 = 0;
    VL_ZERO_RESET_W(76, vlSelf->__VdlyVal__Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory__v0);
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__mem__DOT__dcache_queue__DOT__deq_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__memory__DOT__uartTx__DOT__fifo_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__core__DOT__registers__DOT__bank1_0_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__core__DOT__registers__DOT__bank0_0_ext__DOT__Memory__v0 = 0;
    VL_ZERO_RESET_W(108, vlSelf->__VdlyVal__Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory__v0);
    vlSelf->__VdlyDim0__Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__core__DOT__lsu__DOT__q_q__DOT__ram_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyVal__Main__DOT__vga_controller__DOT__memory_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlyDim0__Main__DOT__vga_controller__DOT__memory_ext__DOT__Memory__v0 = 0;
    vlSelf->__VdlySet__Main__DOT__vga_controller__DOT__memory_ext__DOT__Memory__v0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__reset__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_execute__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_allocate_warps__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_warp_count__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_vga_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_mem_req_ready__0 = 0;
    VL_ZERO_RESET_W(512, vlSelf->__Vtrigprevexpr___TOP__io_mem_resp__0);
    vlSelf->__Vtrigprevexpr___TOP__io_mem_valid__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_rxd__0 = 0;
    vlSelf->__VicoDidInit = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clock__1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__io_vga_clk__1 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}

VL_ATTR_COLD void VMain___024root___ctor_var_reset(VMain___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMain___024root___ctor_var_reset\n"); );
    VMain__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VMain___024root___ctor_var_reset_0(vlSelf);
    VMain___024root___ctor_var_reset_1(vlSelf);
}
