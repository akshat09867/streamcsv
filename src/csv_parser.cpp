#include "streamcsv/csv_parser.hpp"

#include<cmath>
#include<charconv>
#include<string_view>
#include<optional>
#include<vector>

    namespace streamcsv{
        bool next_line(std::string_view& remaining, std::string_view& out_line) noexcept {
            if(remaining.empty()) return false;
            auto pos = remaining.find("\n");
            if(pos==std::string_view::npos){
                out_line = remaining;
                remaining = {};
            }
            else{
             out_line = remaining.substr(0, pos);
             remaining.remove_prefix(pos+1);
            }
            if(!out_line.empty() && out_line.back()=='\r') out_line.remove_suffix(1);
            return true;
        }

        void split_fields(std::vector<std::string_view>& v, std::string_view line, char delimiter){
            v.clear();
            if(line.empty()) return;
            while(!0){
                auto pos = line.find(delimiter);
                if(pos==std::string_view::npos){
                        v.push_back(line);
                        line = {};
                        break;
                }
                v.push_back(line.substr(0, pos));
                line.remove_prefix(pos+1);
            }
        }

        std::optional<double> parse_double(std::string_view v) noexcept {
            if(!v.empty() && v.front() == ' '){
                auto first = v.find_first_not_of(' ');
                if (first != std::string_view::npos) {
                    v.remove_prefix(first);
                }
            }
            if(!v.empty() && v.back() == ' '){
                auto last = v.find_last_not_of(' ');
                if (last != std::string_view::npos) {
                    v.remove_suffix(v.size() - (last + 1));
                }
            }
            double value{};
            auto [ptr, ec] = std::from_chars(v.data(), v.data()+v.size(), value);
            if(ec==std::errc{} && ptr==v.data()+v.size() && std::isfinite(value)){
                return value;
            }
            return std::nullopt;
        }
    }
