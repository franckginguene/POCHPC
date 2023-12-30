#include <iostream>
#include <fstream>

#include <proxyInclude/gtest>
#include <proxyInclude/benchmark>

class MyBenchmarkReporter : public benchmark::ConsoleReporter {
public:
    explicit MyBenchmarkReporter(){}

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

        // Save reports
        m_reports = reports;
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

public:
    
    /**
    * @brief Renvoie le temps moyen du benchmark en seconde
    * On part du principe que l'instance n'a servi qu'au bench d'une seule fonction.
    * Dans les autres cas, la fonction renvoie l'infini
    */
    [[nodiscard]] double getMeanTimeSec() const
    {
        if (m_reports.size() != 1)
        {
            return std::numeric_limits<double>::infinity();
        }
        return m_reports[0].real_accumulated_time / m_reports[0].iterations;
    }

private:
    std::vector<Run> m_reports;
};

void applySin() {
    std::vector<double> a(100'000, 1.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return sin(current); });
}

void applyCos() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return cos(current); });
}

void applyTan() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return tan(current); });
}

void applyAsin() {
    std::vector<double> a(100'000, 1.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return asin(current); });
}

void applyAcos() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return acos(current); });
}

void applyAtan() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return atan(current); });
}

void applyExp() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return exp(current); });
}

void applyLog() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return log(current); });
}
void applyPow() {
    std::vector<double> a(100'000, 2.);
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return pow(current, 1.3); });
}

void applyReferenceExp(std::vector<double> & a) {
    std::transform(a.begin(), a.end(), a.begin(), [](double current) {return exp(current); });
}

// Fonction de benchmark de Google Benchmark pour applySin
static void BM_applySin(benchmark::State& state) {
    for (auto _ : state) {
        applySin();  // Appelez la fonction à mesurer ici
    }
}
static void BM_applyCos(benchmark::State& state) {
    for (auto _ : state) {
        applyCos();
    }
}
static void BM_applyTan(benchmark::State& state) {
    for (auto _ : state) {
        applyTan();
    }
}
static void BM_applyAsin(benchmark::State& state) {
    for (auto _ : state) {
        applyAsin();
    }
}
static void BM_applyAcos(benchmark::State& state) {
    for (auto _ : state) {
        applyAcos();
    }
}
static void BM_applyAtan(benchmark::State& state) {
    for (auto _ : state) {
        applyAtan();
    }
}
static void BM_applyExp(benchmark::State& state) {
    for (auto _ : state) {
        applyExp();
    }
}
static void BM_applyLog(benchmark::State& state) {
    for (auto _ : state) {
        applyLog();
    }
}
static void BM_applyPow(benchmark::State& state) {
    for (auto _ : state) {
        applyPow();
    }
}
static void BM_applyReferenceExp(benchmark::State& state) {
    std::vector<double> a(100'000, 3.);
    for (auto _ : state) {
        applyReferenceExp(a);
    }
}

BENCHMARK(BM_applySin);
BENCHMARK(BM_applyCos);
BENCHMARK(BM_applyTan);
BENCHMARK(BM_applyAsin);
BENCHMARK(BM_applyAcos);
BENCHMARK(BM_applyAtan);
BENCHMARK(BM_applyExp);
BENCHMARK(BM_applyLog);
BENCHMARK(BM_applyPow);
BENCHMARK(BM_applyReferenceExp);

// Test Google Test pour applySin
TEST(MyBenchmark, applySin) {
    // Create an instance of the custom benchmark reporter
    MyBenchmarkReporter custom_reporter;

    // Run the benchmark with the custom reporter. Filtering is necessary.
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_applySin");

    // Assertion Google Test basée sur le temps d'exécution pour applySin en seconde
    EXPECT_LT(custom_reporter.getMeanTimeSec(), 1e-3);
}

// Test Google Test pour applyExp
TEST(MyBenchmark, applyExp) {
    MyBenchmarkReporter custom_reporter;
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_applyExp");
    EXPECT_LT(custom_reporter.getMeanTimeSec(), 1e-3);
}

// Test Google Test pour applyReferenceExp
TEST(MyBenchmark, applyReferenceExp) {
    MyBenchmarkReporter custom_reporter;
    benchmark::RunSpecifiedBenchmarks(&custom_reporter, "BM_applyReferenceExp");
    EXPECT_LT(custom_reporter.getMeanTimeSec(), 1e-3);
}

// Test Google Test pour tout
TEST(MyBenchmark, applyAll) {
    MyBenchmarkReporter custom_reporter;
    benchmark::RunSpecifiedBenchmarks(&custom_reporter);
}

int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Configure Google Benchmark
    ::benchmark::Initialize(&argc, argv);

    // Exécutez les tests Google Test et renvoyez le résultat
    return RUN_ALL_TESTS();
}
