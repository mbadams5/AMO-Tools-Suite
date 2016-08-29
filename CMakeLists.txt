cmake_minimum_required(VERSION 3.5)
project(amo_library)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "*.h" "calculator*.h" "*.cpp" "calculator/*.cpp" )
set(LIB_FILES ${SOURCE_FILES})
list(REMOVE_ITEM LIB_FILES "main.cpp")

#set(SOURCE_FILES main.cpp Pump.cpp Pump.h Motor.cpp Motor.h FieldData.cpp FieldData.h Financial.cpp Financial.h calculator/existing/PumpEfficiency.cpp calculator/existing/PumpEfficiency.h calculator/existing/MotorRatedPower.cpp calculator/existing/MotorRatedPower.h calculator/existing/MotorShaftPower.cpp calculator/existing/MotorShaftPower.h calculator/existing/MotorEfficiency.cpp calculator/existing/MotorEfficiency.h calculator/existing/MotorPowerFactor.cpp calculator/existing/MotorPowerFactor.h calculator/existing/MotorCurrent.cpp calculator/existing/MotorCurrent.h calculator/existing/AnnualEnergy.cpp calculator/existing/AnnualEnergy.h calculator/existing/AnnualSavingsPotential.cpp calculator/existing/AnnualSavingsPotential.h calculator/existing/OptimizationRating.cpp calculator/existing/OptimizationRating.h calculator/existing/MotorPower.cpp calculator/existing/MotorPower.h PSATResult.cpp PSATResult.h calculator/existing/AnnualCost.cpp)
#set(LIB_FILES Pump.cpp Pump.h Motor.cpp Motor.h FieldData.cpp FieldData.h Financial.cpp Financial.h calculator/existing/PumpEfficiency.cpp calculator/existing/PumpEfficiency.h calculator/existing/MotorRatedPower.cpp calculator/existing/MotorRatedPower.h calculator/existing/MotorShaftPower.cpp calculator/existing/MotorShaftPower.h calculator/existing/MotorEfficiency.cpp calculator/existing/MotorEfficiency.h calculator/existing/MotorPowerFactor.cpp calculator/existing/MotorPowerFactor.h calculator/existing/MotorCurrent.cpp calculator/existing/MotorCurrent.h calculator/existing/AnnualEnergy.cpp calculator/existing/AnnualEnergy.h calculator/existing/AnnualSavingsPotential.cpp calculator/existing/AnnualSavingsPotential.h calculator/existing/OptimizationRating.cpp calculator/existing/OptimizationRating.h calculator/existing/MotorPower.cpp calculator/existing/MotorPower.h PSATResult.cpp PSATResult.h calculator/existing/PumpShaftPower.h calculator/existing/PumpShaftPower.cpp calculator/existing/AnnualCost.h calculator/existing/AnnualCost.cpp)
add_executable(amo_library_cmd_line ${SOURCE_FILES})
add_library(amo_library SHARED ${LIB_FILES})