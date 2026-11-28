#pragma once
#include<optional>
#include<string_view>
#include<vector>


namespace streamcsv{
    [[nodiscard]] bool next_line(std::string_view& remaining, std::string_view& out_line) noexcept;

    void split_fields(std::vector<std::string_view>& v, std::string_view line, char delimiter);

    [[nodiscard]] std::optional<double> parse_double(std::string_view v) noexcept;
}
