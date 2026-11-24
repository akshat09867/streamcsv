#include<bits/stdc++.h>
using namespace std;

namespace streamcsv {
    class Mappedfile{
        void cleanup() noexcept;
        int fd_= -1;
        size_t size_=0;
        void* data_=nullptr;
        public:
            explicit Mappedfile(const filesystem::path& path);
            ~Mappedfile();

            Mappedfile(const Mappedfile&) = delete;
            Mappedfile& operator=(const Mappedfile&) = delete;

            Mappedfile(Mappedfile&& other) noexcept;
            Mappedfile& operator=(Mappedfile&& other) noexcept;

            [[nodiscard]] string_view view() const noexcept;
            [[nodiscard]] std::size_t size() const noexcept { return size_; }
            [[nodiscard]] bool empty() const noexcept { return size_ == 0; }

    };
}
