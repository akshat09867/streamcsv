#include "streamcsv/mapped_file.hpp"

#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <system_error>
#include <unistd.h>
using namespace std;

namespace streamcsv{
    Mappedfile::Mappedfile(const filesystem::path& path){
        fd_ = ::open(path.c_str(), O_RDONLY);
        if(fd_==-1){
            throw system_error(errno, system_category(), "Failed to open:" + path.string());
        }
        struct stat st{};
        if(::fstat(fd_, &st)==-1){
            const int err = errno;
            close(fd_);
            throw system_error(err, system_category(), "file doesn't contain metadata");
        }
        size_ = static_cast<size_t>(st.st_size);
        if(size_==0) return;
        void* ptr = ::mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd_, 0);
        if(ptr==MAP_FAILED){
            const int err=errno;
            close(fd_);
            throw system_error(err, system_category(), "Mapping Failed");
        }
        data_ = ptr;
    }
        Mappedfile::~Mappedfile(){
            cleanup();
        }
        Mappedfile::Mappedfile(Mappedfile&& other) noexcept:
        fd_(exchange(other.fd_, -1)),
        data_(exchange(other.data_, nullptr)),
        size_(exchange(other.size_, 0)){}

        Mappedfile& Mappedfile::operator=(Mappedfile&& other) noexcept{
            if (this != &other) {
                    cleanup();
                    fd_ = std::exchange(other.fd_, -1);
                    data_ = std::exchange(other.data_, nullptr);
                    size_ = std::exchange(other.size_, 0);
                }
        return *this;
    }

    string_view  Mappedfile::view() const noexcept{
        if (data_ == nullptr || size_ == 0) {
                return {};
            }
            return {static_cast<const char*>(data_), size_};
    }

    void Mappedfile::cleanup() noexcept{
        if(data_!=nullptr){
            ::munmap(data_, size_);
            data_=nullptr;
            size_=0;
        }
        if(fd_!=1){
            ::close(fd_);
            fd_=-1;
        }
    }


}
