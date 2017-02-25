// This is bbasd/buld/buld_handle_files_embedded_in_vxl_source.cxx

//:
// \file
// \brief
// \author Based on original code by  Firat Kalaycilar (@lems.brown.edu)
// \date Feb 09, 2010

#include<vcl_string.h>
#include<vcl_cstdio.h>
#include<vcl_cstdlib.h>
#include<vcl_iostream.h>
#include<vcl_fstream.h>
#include<vul/vul_file.h>
#include<vul/vul_file_iterator.h>
#include<vpl/vpl.h>

#include "buld_handle_files_embedded_in_vxl_source.h"

bool buld_is_embedded_files_dir_safe = false;

void buld_create_file_extraction_lock(const char* out_dir)
{
    vcl_string expanded_out_dir = vul_file::expand_tilde(out_dir);
    vcl_string lock_file = expanded_out_dir + vcl_string("/.buldrunlock");
    vcl_ofstream lock_stream(lock_file.c_str());
    lock_stream << "BULD_LOCK";
    lock_stream.close();
}

void buld_remove_file_extraction_lock(const char* out_dir)
{
    vcl_string expanded_out_dir = vul_file::expand_tilde(out_dir);
    vcl_string lock_file = expanded_out_dir + vcl_string("/.buldrunlock");
    vpl_unlink(lock_file.c_str());
}

bool buld_is_file_extraction_in_progress(const char* out_dir)
{
    vcl_string expanded_out_dir = vul_file::expand_tilde(out_dir);
    vcl_string lock_file = expanded_out_dir + vcl_string("/.buldrunlock");
    return vul_file_exists(lock_file);
}

void buld_default_extract_embedded_file(char* array, int length, const char* out_dir, char* file_name)
{
    vcl_string expanded_out_dir = vul_file::expand_tilde(out_dir);
    vcl_string out_file = expanded_out_dir + vcl_string("/") + vcl_string(file_name);
    vul_file::make_directory_path(vul_file::dirname(out_file));
    vcl_FILE* pFile = vcl_fopen ( out_file.c_str() , "wb" );
    if(pFile == NULL)
    {
        vcl_cerr << "ERROR: File " <<  out_file << " cannot be created. Cannot continue!" << vcl_endl;
        buld_remove_file_extraction_lock(out_dir);
        vcl_exit(1);
    }
    vcl_fwrite (array, 1 ,length ,pFile);
    vcl_fclose(pFile);
}

void buld_default_delete_extracted_file(const char* out_dir)
{
    if(buld_is_embedded_files_dir_safe)
    {
        vcl_string path = vul_file::expand_tilde(out_dir);
        if(vul_file::is_directory(path))
        {
            vul_file_iterator fit(path + vcl_string("/*"));
            do
            {
                vcl_string entry_name = fit.filename();
                if (entry_name == "." || entry_name == "..")
                {
                    continue;
                }
                vcl_string full_entry_path = path + '/' + entry_name;
                buld_default_delete_extracted_file(full_entry_path.c_str());
            }
            while(++fit);
            vcl_cout << "Deleting " << path.c_str() << vcl_endl;
            vpl_rmdir(path.c_str());
        }
        else
        {
            vcl_cout << "Deleting " << path.c_str() << vcl_endl;
            vpl_unlink(path.c_str());
        }
    }
    else
    {
        vcl_cerr << "Deleting directory " << out_dir << " may be harmful!" << vcl_endl;
        return;
    }
}
