#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <curl/curl.h>
#include <ctime>

namespace curl_testing {
    size_t writeCallback(void* Data, size_t Size_Data_Element, size_t Number_Data_Elements, void* Output_Stream) {
        return fwrite(Data, Size_Data_Element, Number_Data_Elements, (FILE*)Output_Stream);
    }

    void curlDownload(const char* Url, const char* Output_File_Path) {
        CURL* curl;
        CURLcode res;
        FILE* p_file = nullptr;
        clock_t start, end;

        curl = curl_easy_init();
        if (!curl) {
            std::cerr << "Failed to initialize curl." << std::endl;
            return;
        }

        p_file = fopen(Output_File_Path, "wb");
        if (!p_file) {
            std::cerr << "Failed to create file." << std::endl;
            curl_easy_cleanup(curl);
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, Url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, p_file);

        start = clock();

        res = curl_easy_perform(curl);

        end = clock();

        if (res != CURLE_OK) {
            std::cerr << "Curl Error: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Download successful in: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds." << std::endl;
        }

        fclose(p_file);
        curl_easy_cleanup(curl);
    }
}

int main() {
    curl_testing::curlDownload(
        "https://upload.wikimedia.org/wikipedia/commons/thumb/0/06/Alonzo_W._Slayback.jpg/800px-Alonzo_W._Slayback.jpg",
        "curlImage.jpeg"
    );
    return 0;
}
