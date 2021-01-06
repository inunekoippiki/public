#if( _DEBUG )
#include<iostream>
#include<fstream>
#include<filesystem>
using namespace std::filesystem;
using namespace std;

void outText( char type, ofstream& fout, string path ){
    for( const directory_entry& e : directory_iterator( path ) ){
        if( is_directory( e ) ){
            outText( type, fout, e.path().string() );
        }
        else{
            size_t idx = e.path().filename().string().find_last_of( "." );
            fout << type << ' '
                << e.path().filename().string().substr( 0, idx ) << ' '
                << path << '/' << e.path().filename().string() << endl;
        }
    }
}

void listsFile( char type, const char* directory, const char* outfile ){
    ofstream fout( outfile );
    outText( type, fout, directory );
    fout.close();
}
#endif // DEBUG