#ifndef ZIP_FILE_MANAGER_HPP
#define ZIP_FILE_MANAGER_HPP

#include <unzip.h>

#include "log_config.hpp"

class ZipFileManager {
public:
   static ZipFileManager* GetInstance() {
      if (instance_ == 0) {
         instance_ = new ZipFileManager();
      }

      return instance_;
   }

   static void Delete() {
     if (instance_ != NULL) {
        delete instance_;
        instance_ = NULL;
     }
   }

   bool OpenZip(const char* zip_location) {

      zipped_file_ = unzOpen64(zip_location);

      return (zipped_file_ != NULL);
   }

   // This reads a file to a buffer, which the caller then owns. 'filename' is
   // the name of the file and its relative path, with the base directory being
   // the root of the zip file.
   // REQ OpenZip must be called prior to ReadFile being called.
   // TODO Replace pointer with shared pointer.
   char* ReadFile(const char* filename, int& size_read_output) {

      // Finds the file in the zip archive.
      if (unzLocateFile(zipped_file_, filename, 0) != UNZ_OK)
      {
         LOGE("File %s not found in the zipfile\n",filename);
         return 0;
     }

      // Opens the file.
      if (unzOpenCurrentFile(zipped_file_) != UNZ_OK) {
         LOGE("File %s could not be opened\n",filename);
         return 0;
      }

      // Gets the size of the file.
      unz_file_info64 file_info;
      if (unzGetCurrentFileInfo64(zipped_file_,
                                  &file_info,
                                  NULL,
                                  0,
                                  NULL,
                                  0,
                                  NULL,
                                  0)
          != UNZ_OK) {
         LOGE("Could not retrieve file size.\n");
         return 0;
      }

      size_read_output = file_info.uncompressed_size;
      char* buffer = new char[size_read_output];

      unzReadCurrentFile(zipped_file_, buffer, size_read_output);

      return buffer;
   }

private:
   // The instance of the manager.
   static ZipFileManager* instance_;

   // The handle to the zipped file.
   unzFile zipped_file_;

   // This is used to reset file position.
   unz64_file_pos zipped_file_start_position_;
};

#endif
