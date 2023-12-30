#include <AuroraAPI/Simulation.h>
#include <AuroraAPI/Fitness.h>

#include <iostream>

#include <Validator/PerformanceValidator.h>

#include <proxyInclude/gtest>

#include <thread>

// Fonction de benchmark de Google Benchmark
static void BM_launch(benchmark::State& state) {
    Simulation simulation;
    for (auto _ : state) {
        simulation.launch(Fitness::doSomethingWithEigen);
    }
}

BENCHMARK(BM_launch);

// Test Google Test pour applyReferenceExp
TEST(SimulationBenchmark, launch) {
    PerformanceValidator custom_reporter;
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_launch");
    EXPECT_LT(custom_reporter.getMeanTimeSec(), 1e-3);
}

int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Configure Google Benchmark
    ::benchmark::Initialize(&argc, argv);

    // Exécutez les tests Google Test et renvoyez le résultat
    return RUN_ALL_TESTS();
}
