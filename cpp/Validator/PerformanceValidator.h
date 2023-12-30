#pragma once

#include <proxyInclude/benchmark>

/**
* @brief Classe de reporter custom pour l'utilisation de la lib benchmark.
* Ce reporter permet notamment de stocker les résultats pour comparer les temps dans des test gtest.
*/
class PerformanceValidator : public benchmark::ConsoleReporter {
public:
    explicit PerformanceValidator(){}

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