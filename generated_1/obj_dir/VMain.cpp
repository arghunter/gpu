// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VMain__pch.h"

//============================================================
// Constructors

VMain::VMain(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VMain__Syms(contextp(), _vcname__, this)}
    , m_evalLoop{*this, /*convergeLimit:*/ 10000}
    , clock{vlSymsp->TOP.clock}
    , io_vga_clk{vlSymsp->TOP.io_vga_clk}
    , reset{vlSymsp->TOP.reset}
    , io_execute{vlSymsp->TOP.io_execute}
    , io_allocate_warps{vlSymsp->TOP.io_allocate_warps}
    , io_complete{vlSymsp->TOP.io_complete}
    , io_hsync{vlSymsp->TOP.io_hsync}
    , io_vsync{vlSymsp->TOP.io_vsync}
    , io_blanking{vlSymsp->TOP.io_blanking}
    , io_mem_req_ready{vlSymsp->TOP.io_mem_req_ready}
    , io_mem_req_valid{vlSymsp->TOP.io_mem_req_valid}
    , io_mem_req_bits_write{vlSymsp->TOP.io_mem_req_bits_write}
    , io_mem_valid{vlSymsp->TOP.io_mem_valid}
    , io_rxd{vlSymsp->TOP.io_rxd}
    , io_txd{vlSymsp->TOP.io_txd}
    , io_warp_count{vlSymsp->TOP.io_warp_count}
    , io_rgb{vlSymsp->TOP.io_rgb}
    , io_mem_req_bits_addr{vlSymsp->TOP.io_mem_req_bits_addr}
    , io_mem_req_bits_wdata{vlSymsp->TOP.io_mem_req_bits_wdata}
    , io_mem_resp{vlSymsp->TOP.io_mem_resp}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VMain::VMain(const char* _vcname__)
    : VMain(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VMain::~VMain() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VMain___024root___eval_debug_assertions(VMain___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VMain___024root___eval_static(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_initial(VMain___024root* vlSelf);
VL_ATTR_COLD bool VMain___024root___eval_stl(VMain___024root* vlSelf, CData/*0:0*/ firstIteration);
void VMain___024root___eval_sample(VMain___024root* vlSelf);
bool VMain___024root___eval_ico(VMain___024root* vlSelf, CData/*0:0*/ firstIteration);
bool VMain___024root___eval_act(VMain___024root* vlSelf);
bool VMain___024root___eval_inact(VMain___024root* vlSelf);
bool VMain___024root___eval_nba(VMain___024root* vlSelf);
bool VMain___024root___eval_obs(VMain___024root* vlSelf);
bool VMain___024root___eval_react(VMain___024root* vlSelf);
void VMain___024root___eval_postponed(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_final(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__stl(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__ico(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__act(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__nba(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__obs(VMain___024root* vlSelf);
VL_ATTR_COLD void VMain___024root___eval_dump_triggers__react(VMain___024root* vlSelf);

void VMain::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VMain::eval_step\n"); );
    m_evalLoop.eval();
}

void VMain::evalBegin() {
#ifdef VL_DEBUG
    // Debug assertions
    VMain___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
}

void VMain::evalEnd() {
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void VMain::evalStatic() {
    VMain___024root___eval_static(&(vlSymsp->TOP));
}

void VMain::evalInitial() {
    VMain___024root___eval_initial(&(vlSymsp->TOP));
}

bool VMain::evalStl(bool firstIteration) {
    return VMain___024root___eval_stl(&(vlSymsp->TOP), firstIteration);
}

void VMain::evalSample() {
    VMain___024root___eval_sample(&(vlSymsp->TOP));
}

bool VMain::evalIco(bool firstIteration) {
    return VMain___024root___eval_ico(&(vlSymsp->TOP), firstIteration);
}

bool VMain::evalAct() {
    return VMain___024root___eval_act(&(vlSymsp->TOP));
}

bool VMain::evalInact() {
    return VMain___024root___eval_inact(&(vlSymsp->TOP));
}

bool VMain::evalNba() {
    return VMain___024root___eval_nba(&(vlSymsp->TOP));
}

bool VMain::evalObs() {
    return VMain___024root___eval_obs(&(vlSymsp->TOP));
}

bool VMain::evalReact() {
    return VMain___024root___eval_react(&(vlSymsp->TOP));
}

void VMain::evalPostponed() {
    VMain___024root___eval_postponed(&(vlSymsp->TOP));
}

void VMain::evalFinal() {
    VMain___024root___eval_final(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersStl() {
    VMain___024root___eval_dump_triggers__stl(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersIco() {
    VMain___024root___eval_dump_triggers__ico(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersAct() {
    VMain___024root___eval_dump_triggers__act(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersNba() {
    VMain___024root___eval_dump_triggers__nba(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersObs() {
    VMain___024root___eval_dump_triggers__obs(&(vlSymsp->TOP));
}

VL_ATTR_COLD void VMain::dumpTriggersReact() {
    VMain___024root___eval_dump_triggers__react(&(vlSymsp->TOP));
}

//============================================================
// Events and timing
bool VMain::eventsPending() { return false; }

uint64_t VMain::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VMain::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void VMain::final() {
    contextp()->executingFinal(true);
    evalFinal();
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VMain::hierName() const { return vlSymsp->name(); }
const char* VMain::modelName() const { return "VMain"; }
unsigned VMain::threads() const { return 1; }
void VMain::prepareClone() const { contextp()->prepareClone(); }
void VMain::atClone() const {
    contextp()->threadPoolpOnClone();
}
