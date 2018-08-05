/* ------------------------------------------------------------
name: "BasicAMSynthesis"
Code generated with Faust 2.5.34 (https://faust.grame.fr)
Compilation options: cpp, -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __BasicAMSynthesis_H__
#define  __BasicAMSynthesis_H__

/**
 *  @file    GENERATED FROM... audio_board.cpp
 *  @author  Corey Ford
 *  @date    20/07/2018
 *  @version 1.0
 *
 *  @brief The architecture file used to generate DSP classes for the audio development board.
 *  @section DESCRIPTION
 *
 *  For more in depth and detailed usage @see README within the FAUST Export directory!
 */

/************************************************************************
 
	IMPORTANT NOTE : this file contains two clearly delimited sections :
	the ARCHITECTURE section (in two parts) and the USER section. Each section
	is governed by its own copyright and license. Please check individually
	each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include <stdlib.h> //TODO(corey2.ford@live.uwe.ac.uk): can likely strip some of these out down the line.
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

#include <vector>
#include <stack>
#include <string>
#include <map>
#include <iostream>

#include "faust/gui/console.h"
#include "faust/dsp/dsp.h"
#include "faust/misc.h"
#include "faust/audio/channels.h"

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <cmath>
#include <math.h>

float BasicAMSynthesis_faustpower2_f(float value) {
	return (value * value);
	
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS BasicAMSynthesis
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class BasicAMSynthesis : public dsp {
	
 private:
	
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	float fRec0[2];
	float fConst2;
	float fConst3;
	float fVec1[2];
	float fRec2[2];
	float fVec2[2];
	int IOTA;
	float fVec3[4096];
	float fConst4;
	float fRec1[2];
	FAUSTFLOAT fHslider1;
	float fRec3[2];
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	float fConst5;
	FAUSTFLOAT fHslider3;
	float fRec7[2];
	float fRec8[2];
	float fRec6[2];
	float fRec5[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("filename", "BasicAMSynthesis");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.1");
		m->declare("name", "BasicAMSynthesis");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
		
	}
	virtual int getNumOutputs() {
		return 2;
		
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch (channel) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
			
		}
		return rate;
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(192000.0f, max(1.0f, float(fSamplingFreq)));
		fConst1 = (2.0f / fConst0);
		fConst2 = (0.25f * fConst0);
		fConst3 = (1.0f / fConst0);
		fConst4 = (0.5f * fConst0);
		fConst5 = (6.28318548f / fConst0);
		
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(0.10000000000000001f);
		fHslider3 = FAUSTFLOAT(1.0f);
		
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
			
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
			
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec1[l2] = 0.0f;
			
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec2[l3] = 0.0f;
			
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec2[l4] = 0.0f;
			
		}
		IOTA = 0;
		for (int l5 = 0; (l5 < 4096); l5 = (l5 + 1)) {
			fVec3[l5] = 0.0f;
			
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec1[l6] = 0.0f;
			
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec3[l7] = 0.0f;
			
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec4[l8] = 0.0f;
			
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;
			
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec8[l10] = 0.0f;
			
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec6[l11] = 0.0f;
			
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec5[l12] = 0.0f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual BasicAMSynthesis* clone() {
		return new BasicAMSynthesis();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
		
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("BasicAMSynthesis");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->addHorizontalSlider("gain", &fHslider2, 0.100000001f, 0.0f, 1.0f, 0.00100000005f);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("freq", &fHslider0, 1.0f, 20.0f, 4000.0f, 0.00100000005f);
		ui_interface->declare(&fHslider3, "2", "");
		ui_interface->addHorizontalSlider("multiplyer", &fHslider3, 1.0f, 1.0f, 2.0f, 0.00999999978f);
		ui_interface->declare(&fHslider1, "3", "");
		ui_interface->addHorizontalSlider("mod depth", &fHslider1, 1.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.00100000005f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = (0.00100000005f * float(fHslider2));
		float fSlow3 = (0.00100000005f * float(fHslider3));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec0[0] = (fSlow0 + (0.999000013f * fRec0[1]));
			float fTemp0 = max(fRec0[0], 23.4489498f);
			float fTemp1 = max(20.0f, fabsf(fTemp0));
			fVec1[0] = fTemp1;
			float fTemp2 = (fRec2[1] + (fConst3 * fVec1[1]));
			fRec2[0] = (fTemp2 - floorf(fTemp2));
			float fTemp3 = BasicAMSynthesis_faustpower2_f(((2.0f * fRec2[0]) + -1.0f));
			fVec2[0] = fTemp3;
			float fTemp4 = ((float(iVec0[1]) * (fTemp3 - fVec2[1])) / fTemp1);
			fVec3[(IOTA & 4095)] = fTemp4;
			float fTemp5 = max(0.0f, min(2047.0f, (fConst4 / fTemp0)));
			int iTemp6 = int(fTemp5);
			float fTemp7 = floorf(fTemp5);
			fRec1[0] = ((0.999000013f * fRec1[1]) + (fConst2 * ((fTemp4 - (fVec3[((IOTA - iTemp6) & 4095)] * (fTemp7 + (1.0f - fTemp5)))) - ((fTemp5 - fTemp7) * fVec3[((IOTA - (iTemp6 + 1)) & 4095)]))));
			fRec3[0] = (fSlow1 + (0.999000013f * fRec3[1]));
			fRec4[0] = (fSlow2 + (0.999000013f * fRec4[1]));
			fRec7[0] = (fSlow3 + (0.999000013f * fRec7[1]));
			float fTemp8 = (fRec0[0] * fRec7[0]);
			fRec8[0] = (fRec8[1] + (fConst5 * (fTemp8 * (0.0f - fRec5[1]))));
			fRec6[0] = ((fRec6[1] + (fConst5 * (fTemp8 * fRec8[0]))) + float((1 - iVec0[1])));
			fRec5[0] = fRec6[0];
			float fTemp9 = (fConst1 * ((((fRec0[0] * fRec1[0]) * fRec3[0]) * fRec4[0]) * (fRec5[0] + 1.0f)));
			output0[i] = FAUSTFLOAT(fTemp9);
			output1[i] = FAUSTFLOAT(fTemp9);
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			fVec2[1] = fVec2[0];
			IOTA = (IOTA + 1);
			fRec1[1] = fRec1[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			
		}
		
	}

	
};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

BasicAMSynthesis	DSP; //declared global by faust

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif
