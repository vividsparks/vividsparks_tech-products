// Copyright (c) 2020, VividSparks IT Solutions Pvt. Ltd.  All rights reserved.
//
// Redistribution and use in source and binary forms, modifications,
// are NOT permitted.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// This file implements the SimulatorWrapper object, which hides
// differences in simulators.

#include <RacEr_manycore_simulator.hpp>
#include <svdpi.h>

extern "C" {
        void RacEr_dpi_next();
}

SimulationWrapper::SimulationWrapper(){
        root = new std::string("replicant_tb_top");
        std::string mc_dpi = *root + ".mc_dpi";
        top = svGetScopeFromName(mc_dpi.c_str());
}

// Does nothing. Turning on/off assertions is only supported in
// Verilator.
void SimulationWrapper::assertOn(bool val){

}

std::string SimulationWrapper::getRoot(){
        return *root;
}

void SimulationWrapper::eval(){
        svScope prev;
        prev = svSetScope(top);
        RacEr_dpi_next();
        svSetScope(prev);
}

SimulationWrapper::~SimulationWrapper(){
        this->top = nullptr;
}
