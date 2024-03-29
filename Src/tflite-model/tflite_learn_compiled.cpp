
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 25.07.2023 10:50:57

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX) || defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
constexpr int kTensorArenaSize = 1344;
#else
constexpr int kTensorArenaSize = 320;
#endif

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

typedef struct {
  TfLiteTensor tensor;
  int16_t index;
} TfLiteTensorWithIndex;

typedef struct {
  TfLiteEvalTensor tensor;
  int16_t index;
} TfLiteEvalTensorWithIndex;

TfLiteContext ctx{};
static const int MAX_TFL_TENSOR_COUNT = 4;
static TfLiteTensorWithIndex tflTensors[MAX_TFL_TENSOR_COUNT];
static const int MAX_TFL_EVAL_COUNT = 4;
static TfLiteEvalTensorWithIndex tflEvalTensors[MAX_TFL_EVAL_COUNT];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[4];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,84 } };
const TfArray<1, float> quant0_scale = { 1, { 0.38477268815040588, } };
const TfArray<1, int> quant0_zero = { 1, { -105 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(16) int8_t tensor_data1[20*84] = { 
  -11, 11, 12, 17, 11, -6, -33, -23, 10, -12, -6, -24, -4, 19, 11, 18, 17, -13, 7, -9, 17, 2, 24, -4, -6, -2, -16, 4, -6, -18, -22, 6, 20, -2, -8, -58, -5, -3, -20, -17, 36, 16, 13, 11, -13, 20, 37, -31, -32, 5, -25, -6, -44, -6, -1, 5, 5, -48, -47, -13, -26, 19, 14, -38, 3, 17, 20, 30, 19, -13, 17, -9, 1, -9, 1, 9, 13, 12, -83, 16, 19, 14, 8, 9, 
  10, -56, -61, -12, -6, 24, 20, 9, -28, 20, 12, -1, -3, -57, -3, 4, 4, 16, 50, -33, -27, -14, -8, -42, -28, -42, 7, 13, -2, -1, 12, 15, -21, 3, -26, 76, 6, 7, 5, -12, -23, -13, 11, 11, -4, -11, -5, 4, -1, -31, 30, 22, -26, -5, 11, -3, -10, 49, 27, -2, 28, -7, -30, 42, -37, -26, 10, -28, 20, -6, -12, 21, 6, -15, 1, 16, 0, 32, 127, -4, 20, 2, -19, -3, 
  11, -39, -35, 0, -9, 11, -8, -16, -34, 11, 1, 5, -9, -19, 21, -1, 1, -10, 12, -15, 25, -4, 6, 10, 3, 22, 7, -2, 8, 7, 5, 4, -23, 20, -13, 59, 22, 2, -8, -7, -9, -4, 11, 13, 10, -26, -28, 34, 53, -41, 51, 34, 34, 22, 8, 11, 21, 51, 52, 48, 45, -53, -54, 34, -12, -51, -50, -36, 5, 12, 24, 26, 11, -8, -37, 47, 21, 32, 65, 27, 37, 23, -16, 11, 
  -20, -24, -34, -6, -5, 19, -2, 21, 6, 28, -10, -4, 3, 4, -1, -11, -7, -22, -1, 29, -3, 1, 3, 16, 5, 34, -9, -3, 13, -17, -20, -1, -16, 1, 10, 18, -4, 11, -17, 16, -18, -25, -7, 8, -16, -24, 1, 0, 24, 6, 10, 4, -6, 31, -12, -9, 13, -2, 11, 5, -1, -25, -22, 18, -12, -11, -27, -35, -19, 7, 12, -6, 8, -3, -4, -6, -15, -3, 2, 4, 3, -16, -28, -3, 
  4, 28, 8, -16, -22, 35, 15, 16, -2, 32, 44, 27, -24, 3, -10, 0, -8, -6, 2, 10, 1, -16, -15, -2, -17, -14, 18, 9, 23, 18, 20, -37, -23, 26, 16, -12, -21, 32, 26, 13, -2, -4, -6, -7, -20, 8, 22, 7, -1, 42, 7, -30, -9, -23, 28, 2, 16, -27, -5, -39, -41, 37, 32, 19, 18, 37, 51, 27, -36, -9, -1, -8, -8, 30, 25, -18, -21, -37, -72, -12, -45, -20, 21, -1, 
  6, -22, -16, -11, -7, 9, 19, 9, -13, -5, 9, -1, 4, 0, 10, 0, -13, 13, 18, 11, -12, -20, 3, -13, -17, 2, -3, -11, 7, 11, 13, 5, -6, 22, -2, 42, -20, 11, 32, -4, -29, 2, 13, 8, -8, -3, -46, 39, 17, -13, 28, 18, 19, 10, -3, 10, 0, 30, 49, 20, 22, -24, -4, 11, 27, -20, -7, -13, 6, -3, -21, -11, -12, -19, -16, -6, 9, 35, 48, 11, -9, 7, -3, -2, 
  -6, 81, 63, 23, 31, -26, -25, -44, -33, -21, -64, -44, -14, 2, 25, 16, 8, -59, -71, 71, 72, 10, 3, 56, 90, 70, 2, 8, 11, 17, 30, -11, -9, 0, -4, 23, 21, 16, -25, -4, -18, 4, -5, 4, 11, -59, -50, 79, 70, -5, 22, 60, 82, 51, -13, 1, -4, 48, 41, 75, 84, -80, -70, -19, 0, -89, -93, -79, -38, 1, -9, 30, 17, -44, -60, 42, 53, 0, -14, 54, 75, 53, 22, 6, 
  -3, -62, -92, -31, -42, 38, 33, 9, 18, 12, 44, 17, -33, -32, -8, 0, 1, 40, 61, -64, -59, -37, -27, -56, -72, -69, 2, 9, 11, -3, -31, -3, -37, 8, 19, 24, -42, 21, 44, 23, -8, -39, 15, -14, -14, 64, 40, -23, -41, 19, 40, -38, -71, -27, 5, 5, 3, 4, -20, -41, -19, 31, 28, 47, -28, 30, 45, 12, -10, -8, -13, 8, -13, 68, 45, -29, -42, -12, 73, -32, -55, -30, -3, 1, 
  12, -57, -58, -57, -31, 44, 37, 33, 25, 26, 29, 57, -16, -25, -12, -9, 5, 55, 78, -66, -61, -20, 2, -70, -88, -44, -24, 6, 23, -18, -23, -8, -27, 22, 28, -3, -34, 17, 24, 19, 20, -33, -6, 11, -6, 58, 68, -47, -69, 32, -21, -70, -67, -69, -5, 7, -8, -29, -25, -60, -63, 76, 54, 44, 9, 80, 61, 67, 1, -15, 15, -21, 0, 68, 34, -30, -41, 2, 32, -52, -80, -54, -3, 0, 
  9, 13, 11, 41, 19, -25, -39, -29, 15, -36, -50, -38, 4, -15, 9, 4, 18, -35, -38, 36, 63, 9, -2, 70, 81, 41, -9, -1, 23, -4, -29, 18, 4, -16, -12, 10, 31, 6, -38, 6, -18, -33, 16, 26, 21, -59, -24, 38, 38, -17, -11, 64, 42, 64, 7, -8, -3, 12, 31, 51, 23, -44, -25, -37, 17, -26, -38, -52, 24, 5, 13, 15, 16, -43, -36, 47, 60, 46, 40, 35, 65, 33, -10, 1, 
  -10, 33, 32, -29, 0, -1, 28, 1, -16, 28, 30, 31, 4, 29, 5, -10, -9, 6, -17, 14, -2, -9, 8, -18, -13, 5, -5, 7, 13, 20, 53, -30, -33, 17, 41, 12, -30, 24, 26, 20, -13, 13, 22, 16, 6, 0, -17, 30, 5, 21, 40, 0, 3, 9, 17, -10, 6, 33, 0, 3, -9, 5, 23, -5, -6, 0, 30, 5, -32, -1, -2, -5, -14, -3, 6, -13, -23, -58, -43, 2, -4, 7, 13, 0, 
  17, -4, -16, -20, -14, 26, 22, 43, 21, 32, 23, 30, -29, 2, -8, 10, 4, 65, 73, -44, -45, -30, -22, -49, -56, -66, -8, 14, -8, 31, 4, -6, -28, 4, 30, -20, -15, 23, 49, 6, 19, 3, -14, -17, -17, 34, -2, -23, -31, 22, -1, -32, -42, -12, 16, -6, 16, 10, -16, -23, -23, 21, 37, 31, 1, 37, 53, 15, -6, 11, -10, -16, -9, 49, 16, -19, -41, -9, 14, -31, -69, -34, 12, 22, 
  6, 41, 32, 7, 32, -16, -17, -23, 4, 0, -27, -26, 0, 25, 15, -19, 8, -17, -32, 8, -4, 18, 38, 15, 7, 16, -4, 2, 12, -14, 6, 13, 10, 0, -33, -33, 13, -19, -43, 0, 6, 14, 1, 14, -1, -14, 30, -23, -5, -5, -38, -5, -1, -13, 11, 10, 12, -26, -15, 12, -23, -5, 8, -25, 7, 13, 7, 17, 37, -25, -19, -12, 8, -27, -25, 21, 20, 20, -67, 28, 40, 19, 2, -9, 
  -3, 15, 5, -16, -27, 14, 43, 9, -13, 42, 59, 44, 2, 9, -3, -3, -18, 10, 21, 3, -34, -28, 9, -29, -43, -7, 14, 0, 13, 16, 6, -8, -11, 26, 34, 35, -6, 10, 48, 4, -22, 9, 10, -15, -21, 17, -9, -5, -12, 47, 11, -28, -15, -21, 15, 5, -2, 19, -16, -21, 4, 1, 25, 23, 3, 18, 22, 18, -35, 17, 10, -28, -16, 34, 37, -37, -22, -26, -20, -10, -35, -38, 14, -1, 
  -2, 36, 72, 23, 42, -35, -23, -7, 6, -38, -58, -35, 2, 7, 12, 3, -3, -79, -83, 66, 70, 28, -6, 76, 90, 70, -6, -1, 1, 5, 7, 2, 24, 4, 18, -59, 13, 1, -41, -6, -5, -18, 22, -9, 1, -40, -5, 3, 43, 24, -47, 31, 58, 39, 11, -3, 5, -14, -2, 2, -40, 31, 15, -31, -3, 20, 11, 35, -34, -12, 23, 7, 27, -34, -32, 24, 40, -28, -116, 25, 49, 9, 16, 13, 
  -13, -4, -27, -5, -12, 20, -1, -2, -19, 24, -1, 18, -10, -15, 17, -14, -2, -3, -9, 35, 23, -18, -9, -2, 15, 7, -7, 6, 1, -8, -27, -37, -34, 31, 28, 31, -11, 29, 20, 32, -11, -37, 15, -2, -8, -20, -69, 69, 31, 15, 28, 43, 49, 39, 10, 6, -3, 28, 34, 3, 41, -37, -40, 14, -11, -17, -29, -42, -12, 3, 15, -2, 8, -8, -22, 32, -1, -13, 51, 20, 10, 20, 26, -10, 
  -14, 37, 32, 44, 38, -38, -42, -28, -2, -35, -35, -56, -18, -13, -12, 9, 13, 44, 23, -41, -42, -33, 3, -22, -9, -29, 5, -6, 16, 38, 22, 38, 40, -30, -37, 1, 13, -47, -56, -34, 31, 33, -11, -13, 9, 35, 43, -21, -12, -16, 11, -16, -22, -25, -27, 9, -22, 4, 6, 16, 17, -30, -20, 6, 10, -16, -21, -3, 2, 15, -14, -16, 3, -10, 26, -41, 10, 9, 4, 23, 14, 23, 24, -15, 
  -8, 3, -17, -7, 33, -12, -11, 5, -5, -8, -17, -2, -1, 10, -3, -5, 1, -17, -24, 26, -3, 12, 13, -1, 31, 12, -20, 16, 9, -5, -5, 5, 2, 5, -22, -2, 29, 1, -19, 1, -29, 11, -17, 17, 20, 13, 19, 10, 5, -39, -30, 18, -7, 22, 30, 1, -2, -13, 0, 1, 27, -18, -2, 13, 30, -20, -31, -22, -1, 10, 12, 16, -13, -28, 5, 18, -5, -2, 9, -5, 34, -6, -36, -12, 
  -18, 2, 21, 35, 30, -12, -19, -27, -14, -24, -33, -32, 19, 3, -13, 8, -12, 16, 4, -22, -7, -23, 2, -1, -21, -34, 10, -14, -2, 7, 17, 26, 34, -18, -11, 4, 16, -21, -13, -8, 12, -15, 1, -12, 13, 32, 3, -9, -8, -7, 1, -34, -22, -26, 12, -28, -10, 1, -27, 18, 12, -17, 6, -29, 21, -2, -21, 7, -9, 8, -6, -18, -15, -6, 30, -25, -22, -7, 12, -14, -16, 6, 14, -11, 
  -2, -2, 1, 24, 16, -7, -15, -34, 32, 4, -25, 1, 23, -7, 19, 8, 7, -13, 14, -15, -11, 21, 37, -16, 7, 17, 1, 11, -15, -27, -27, 13, 40, -12, -18, -24, 30, -32, -26, -27, 6, -3, 18, 12, -5, 17, 30, -17, -26, -49, -4, -2, -32, -20, -12, 2, 18, -42, -23, -7, -14, 1, 15, -47, -3, 24, 19, 22, 50, -22, 15, -4, 8, -20, -15, 14, 21, 32, -12, 28, 17, 29, -23, 5, 
};
const TfArray<2, int> tensor_dimension1 = { 2, { 20,84 } };
const TfArray<1, float> quant1_scale = { 1, { 0.012974470853805542, } };
const TfArray<1, int> quant1_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant1 = { (TfLiteFloatArray*)&quant1_scale, (TfLiteIntArray*)&quant1_zero, 0 };
const ALIGN(16) int32_t tensor_data2[20] = { 5, 19, 28, -6, 13, -9, 20, 9, 18, 21, 14, 8, -4, -10, 23, -4, 1, -2, -14, 6, };
const TfArray<1, int> tensor_dimension2 = { 1, { 20 } };
const TfArray<1, float> quant2_scale = { 1, { 0.0049922219477593899, } };
const TfArray<1, int> quant2_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant2 = { (TfLiteFloatArray*)&quant2_scale, (TfLiteIntArray*)&quant2_zero, 0 };
const ALIGN(16) int8_t tensor_data3[20*20] = { 
  -60, 56, 72, -27, -67, 14, 98, 2, -27, 8, 63, -47, -48, 57, -67, -49, 37, 44, 62, 45, 
  -52, -34, 16, 51, 22, 35, -10, -80, -64, 43, 26, -13, -16, -24, 54, 73, 30, 17, 26, -31, 
  -43, 3, 20, 0, 89, -18, -29, 52, 23, -106, 96, 22, 20, 2, 6, 43, 3, -52, 52, -20, 
  -1, 1, 35, 49, 59, 41, -34, 0, 39, 68, -73, 50, 60, -73, 42, 14, -22, 20, -40, 76, 
  16, -62, -56, -44, -37, -7, -16, -33, 1, 98, 57, 6, 70, -5, 53, 36, -111, -35, 5, 58, 
  36, -55, -48, 6, 56, -69, -52, -37, -61, -53, 37, -13, -42, -57, -63, 55, 42, -17, 45, 58, 
  71, 43, 51, 13, 63, -30, -98, 27, 78, 38, 36, -48, -37, 7, 79, -23, 34, -4, 1, 74, 
  -36, -46, -10, -20, 89, 88, -21, 25, -1, -34, 92, 57, -97, 51, -11, 53, 20, -51, -47, 1, 
  -69, 35, 70, 48, -37, 26, 80, -56, -120, 28, -49, 4, 32, 0, 60, 107, -25, 67, 2, -35, 
  -18, 13, -50, 45, 47, -13, -55, -55, 61, -23, 22, -47, -34, -24, 18, -2, 14, 25, 11, -55, 
  -2, 11, -39, 11, -59, -36, 53, 1, 9, 8, -30, -12, -55, -32, -28, -24, -28, 31, 6, 13, 
  30, 7, 8, -36, -53, -68, -28, -63, 51, -57, 51, 50, 85, 43, 38, -36, 70, 6, -25, 37, 
  60, -50, -5, -35, 98, -18, -113, 10, 108, -44, -23, 75, 11, 43, 68, -52, -37, 36, -60, -27, 
  -30, -40, 14, 30, -19, 54, -52, 107, 60, -82, 89, 75, -75, 68, -2, 24, 10, -52, 36, -58, 
  32, -88, 68, 4, 53, -92, 120, -36, -100, 35, 75, 59, 10, -48, 38, -82, 1, 35, -12, 37, 
  58, 23, -2, -9, -82, 46, 31, 49, 4, 93, -17, -7, 16, -93, -25, 50, -6, 43, 40, -11, 
  -28, 50, -29, 17, 33, 35, -13, -6, -14, -43, 4, 21, 28, -61, 17, -35, 52, -46, 24, -54, 
  31, -68, -12, -65, -2, 55, 65, -76, -69, 53, 50, -78, 22, -13, 36, 43, -30, -52, 19, 18, 
  46, -29, -11, -50, -7, 41, 86, -6, 17, -4, 70, -15, -26, 62, 43, -12, -1, 11, -27, -85, 
  -6, 127, 43, -50, -10, 43, -23, 44, 80, 56, -7, 67, -36, -58, -88, 8, 40, -25, 13, -15, 
};
const TfArray<2, int> tensor_dimension3 = { 2, { 20,20 } };
const TfArray<1, float> quant3_scale = { 1, { 0.0057525727897882462, } };
const TfArray<1, int> quant3_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant3 = { (TfLiteFloatArray*)&quant3_scale, (TfLiteIntArray*)&quant3_zero, 0 };
const ALIGN(16) int32_t tensor_data4[20] = { 36, 45, -2, 209, 24, -23, 139, 109, 70, -5, 0, -21, 80, -65, 80, -7, -54, -61, 31, 0, };
const TfArray<1, int> tensor_dimension4 = { 1, { 20 } };
const TfArray<1, float> quant4_scale = { 1, { 0.00095347681781277061, } };
const TfArray<1, int> quant4_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant4 = { (TfLiteFloatArray*)&quant4_scale, (TfLiteIntArray*)&quant4_zero, 0 };
const ALIGN(16) int8_t tensor_data5[5*20] = { 
  15, -8, -48, 36, -22, 38, 10, -115, 49, -24, -58, -30, -75, -69, -32, 66, -44, 10, -102, 89, 
  40, -56, 21, -91, 15, 9, -72, 20, -52, 15, 24, 61, -10, 44, 13, 49, -20, 16, 0, 13, 
  -62, 99, -5, -29, 21, -9, -17, 37, 76, -34, 48, -55, 1, -48, 25, -36, 8, 82, 74, -39, 
  -127, -94, 26, 48, 22, 4, 54, -99, -88, -37, 58, 59, 48, -67, 6, 37, 29, -47, -22, -65, 
  3, 50, 62, -8, -50, -26, 18, 81, -16, -48, -43, -16, 58, 68, -94, -90, -12, 3, -3, 63, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 5,20 } };
const TfArray<1, float> quant5_scale = { 1, { 0.0081284930929541588, } };
const TfArray<1, int> quant5_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant5 = { (TfLiteFloatArray*)&quant5_scale, (TfLiteIntArray*)&quant5_zero, 0 };
const ALIGN(16) int32_t tensor_data6[5] = { 87, -58, -70, 56, 17, };
const TfArray<1, int> tensor_dimension6 = { 1, { 5 } };
const TfArray<1, float> quant6_scale = { 1, { 0.0014698297018185258, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,20 } };
const TfArray<1, float> quant7_scale = { 1, { 0.16574789583683014, } };
const TfArray<1, int> quant7_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const TfArray<2, int> tensor_dimension8 = { 2, { 1,20 } };
const TfArray<1, float> quant8_scale = { 1, { 0.18082438409328461, } };
const TfArray<1, int> quant8_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,5 } };
const TfArray<1, float> quant9_scale = { 1, { 0.55972647666931152, } };
const TfArray<1, int> quant9_zero = { 1, { 54 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,5 } };
const TfArray<1, float> quant10_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant10_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,1,2 } };
const TfArray<1, int> outputs0 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 7,3,4 } };
const TfArray<1, int> outputs1 = { 1, { 8 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 8,5,6 } };
const TfArray<1, int> outputs2 = { 1, { 9 } };
const TfLiteSoftmaxParams opdata3 = { 1 };
const TfArray<1, int> inputs3 = { 1, { 9 } };
const TfArray<1, int> outputs3 = { 1, { 10 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension0, 84, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 1680, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant1))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 80, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant2))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 400, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant3))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 80, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant4))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 100, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant5))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 96, (TfLiteIntArray*)&tensor_dimension7, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension8, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 32, (TfLiteIntArray*)&tensor_dimension9, 5, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension10, 5, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_SOFTMAX, },
};

static void init_tflite_tensor(size_t i, TfLiteTensor *tensor) {
  tensor->type = tensorData[i].type;
  tensor->is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  tensor->allocation_type = tensorData[i].allocation_type;
#else
  tensor->allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
  tensor->bytes = tensorData[i].bytes;
  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  if(tensor->allocation_type == kTfLiteArenaRw){
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
      tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
  tensor->quantization = tensorData[i].quantization;
  if (tensor->quantization.type == kTfLiteAffineQuantization) {
    TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
    tensor->params.scale = quant->scale->data[0];
    tensor->params.zero_point = quant->zero_point->data[0];
  }

}

static void init_tflite_eval_tensor(int i, TfLiteEvalTensor *tensor) {
  if (i < 0) {
    tensor->data.data = nullptr;
    tensor->dims = nullptr;
    return;
  }

  tensor->type = tensorData[i].type;

  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  auto allocation_type = tensorData[i].allocation_type;
  if(allocation_type == kTfLiteArenaRw) {
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
    tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
}

static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  if (current_location - bytes < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArena(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBuffer(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBuffer(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static const uint16_t TENSOR_IX_UNUSED = 0x7FFF;

static void ResetTensors() {
  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    tflTensors[ix].index = TENSOR_IX_UNUSED;
  }
  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    tflEvalTensors[ix].index = TENSOR_IX_UNUSED;
  }
}

static TfLiteTensor* GetTensor(const struct TfLiteContext* context,
                               int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    // already used? OK!
    if (tflTensors[ix].index == tensor_idx) {
      return &tflTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_tensor(tensor_idx, &tflTensors[ix].tensor);
      tflTensors[ix].index = tensor_idx;
      return &tflTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_TENSOR_COUNT (%d)\n", MAX_TFL_TENSOR_COUNT);
  return nullptr;
}

static TfLiteEvalTensor* GetEvalTensor(const struct TfLiteContext* context,
                                       int tensor_idx) {

  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    // already used? OK!
    if (tflEvalTensors[ix].index == tensor_idx) {
      return &tflEvalTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflEvalTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_eval_tensor(tensor_idx, &tflEvalTensors[ix].tensor);
      tflEvalTensors[ix].index = tensor_idx;
      return &tflEvalTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_EVAL_COUNT (%d)\n", (int)MAX_TFL_EVAL_COUNT);
  return nullptr;
}

} // namespace

TfLiteStatus tflite_learn_65_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArena;
  ctx.GetScratchBuffer = &GetScratchBuffer;
  ctx.GetTensor = &GetTensor;
  ctx.GetEvalTensor = &GetEvalTensor;
  ctx.tensors_size = 11;
  for (size_t i = 0; i < 11; ++i) {
    TfLiteTensor tensor;
    init_tflite_tensor(i, &tensor);
    if (tensor.allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tensor.data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 4; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 4; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      ResetTensors();

      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteStatus tflite_learn_65_input(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(inTensorIndices[index], tensor);
  return kTfLiteOk;
}

static const int outTensorIndices[] = {
  10, 
};
TfLiteStatus tflite_learn_65_output(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(outTensorIndices[index], tensor);
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_65_invoke() {
  for (size_t i = 0; i < 4; ++i) {
    ResetTensors();

    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_65_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
