#include "IEvaluator.h"
#include "TopBitEvaluator.h"
#include "CategoriesEvaluator.h"

/*
#include "PredictBitCircuitEvaluator.h"
#include "PredictByteCircuitEvaluator.h"
#include "PredictBitGroupParityCircuitEvaluator.h"
#include "PredictBytesParityCircuitEvaluator.h"
#include "PredictHammingWeightCircuitEvaluator.h"
#include "DistinguishTwoEvaluator.h"
#include "OutputCategoriesEvaluator.h"
*/

IEvaluator::IEvaluator(int type) : m_type(type) { }

IEvaluator *IEvaluator::getStandardEvaluator(int type) {
    if (type >= EVALUATOR_PROJECT_SPECIFIC_MINIMUM) {
        mainLogger.out(LOGGER_WARNING) << "Evaluator constant in the project range (" << type << ")." << endl;
        return NULL;
    }
    switch (type) {
    case EVALUATOR_TOP_BIT:
        return new TopBitEvaluator();
        break;
    case EVALUATOR_CATEGORIES:
        return new CategoriesEvaluator();
        break;
        /*
    case EVALUATOR_BIT:
        return new PredictBitCircuitEvaluator();
        break;
    case EVALUATOR_BITGROUP_PARITY:
        return new PredictBitGroupParityCircuitEvaluator();
        break;
    case EVALUATOR_BYTES_PARITY:
        return new PredictBytesParityCircuitEvaluator();
        break;
    case EVALUATOR_HAMMING_WEIGHT:
        return new PredictHammingWeightCircuitEvaluator();
        break;
    case EVALUATOR_BYTE:
        return new PredictByteCircuitEvaluator();
        break;
    case EVALUATOR_DISTINGUISH:
        return new DistinguishTwoEvaluator();
        break;
	case EVALUATOR_OUTPUT_CATEGORIES:
        return new OutputCategoriesEvaluator();
        break;
        */
    default:
        mainLogger.out(LOGGER_ERROR) << "Unknown evaluator type \"" << type << "\"." << endl;
        return NULL;
        break;
    }
}
