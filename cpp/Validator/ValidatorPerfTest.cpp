#include <gtest/gtest.h>
#include <benchmark/include/benchmark/benchmark.h>
#include <iostream>
#include <fstream>

class MyBenchmarkReporter : public benchmark::ConsoleReporter {
public:
    //explicit MyBenchmarkReporter(std::ostream& output_stream)
    //    : output_stream_(output_stream) {}
    explicit MyBenchmarkReporter(std::ostream& output_stream)
        : output_stream_(output_stream) {}

    void ReportRuns(const std::vector<Run>& reports) override {
        for (const auto& run : reports) {
            // print the header:
            // --- if none was printed yet
            bool print_header = !printed_header_;
            // --- or if the format is tabular and this run
            //     has different fields from the prev header
            //print_header |= (output_options_ & OO_Tabular) &&
            //    (!internal::SameNames(run.counters, prev_counters_));
            if (print_header) {
                printed_header_ = true;
                prev_counters_ = run.counters;
                PrintHeader(run);
            }
            // As an alternative to printing the headers like this, we could sort
            // the benchmarks by header and then print. But this would require
            // waiting for the full results before printing, or printing twice.
            PrintRunData(run);
        }
    }

    bool ReportContext(const Context& context) override
    {
        name_field_width_ = context.name_field_width;
        printed_header_ = false;
        prev_counters_.clear();

        PrintBasicContext(&GetErrorStream(), context);

#ifdef BENCHMARK_OS_WINDOWS
        if ((output_options_ & OO_Color) && &std::cout != &GetOutputStream()) {
            GetErrorStream()
                << "Color printing is only supported for stdout on windows."
                " Disabling color printing\n";
            output_options_ = static_cast<OutputOptions>(output_options_ & ~OO_Color);
        }
#endif
        // if return "false", the benchmark run is never started
        return true;
    }


private:
    std::ostream& output_stream_;
};

void myFunction1() {
    // ... implémentation de la fonction ...
    std::vector<double> a(100'000, 1.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return sin(current); });
}

void myFunction2() {
    // ... implémentation de la fonction ...
    std::vector<double> a(100'000, 1.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return sin(current); });
}

// Fonction de benchmark de Google Benchmark pour myFunction1
static void BM_MyFunction1(benchmark::State& state) {
    for (auto _ : state) {
        myFunction1();  // Appelez la fonction à mesurer ici
    }
}
// Fonction de benchmark de Google Benchmark pour myFunction1
static void BM_MyFunction2(benchmark::State& state) {
    for (auto _ : state) {
        myFunction2();  // Appelez la fonction à mesurer ici
    }
}
BENCHMARK(BM_MyFunction1);
BENCHMARK(BM_MyFunction2);

// Test Google Test pour myFunction1
TEST(MyBenchmark, MyFunction1) {
    // Redirect benchmark results to a file
    std::ofstream output_file("benchmark_results.txt");

    // Create an instance of the custom benchmark reporter
    MyBenchmarkReporter custom_reporter(output_file);

    // Run the benchmark with the custom reporter
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_MyFunction1");

    // Assertion Google Test basée sur le temps d'exécution pour myFunction1
    //EXPECT_LT(avg_time, 1.0);  // Vous pouvez ajuster la durée souhaitée ici
}

// Test Google Test pour myFunction2
TEST(MyBenchmark, MyFunction2) {
    // Redirect benchmark results to a file
    std::ofstream output_file("benchmark_results.txt");

    // Create an instance of the custom benchmark reporter
    MyBenchmarkReporter custom_reporter(output_file);

    // Run the benchmark with the custom reporter
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_MyFunction2");

    // Assertion Google Test basée sur le temps d'exécution pour myFunction1
    //EXPECT_LT(avg_time, 1.0);  // Vous pouvez ajuster la durée souhaitée ici
}

int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Configure Google Benchmark
    ::benchmark::Initialize(&argc, argv);

    // Exécutez les tests Google Test et renvoyez le résultat
    return RUN_ALL_TESTS();
}
