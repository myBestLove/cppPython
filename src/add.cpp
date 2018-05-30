#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API

#include <boost/python.hpp>
#include <pyboostcvconverter/pyboostcvconverter.hpp>
#include <Python.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <sys/time.h>




using namespace cv;
using namespace std;
using namespace pbcvt;

    using namespace boost::python;



#if (PY_VERSION_HEX >= 0x03000000)

    static void *init_ar() {
#else
        static void init_ar(){
#endif
        Py_Initialize();

        import_array();
        return NUMPY_IMPORT_ARRAY_RETVAL;
    }


    
int add(int a, int b)
{



    PyObject *pModule,*pFunc,*pDict;
    PyObject * pArgs,*pValue;


    /* import */
    pModule = PyImport_ImportModule("add_module");
    if (pModule == NULL) {  
        cout<<"ERROR importing module"<<endl;  
    } 


    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference
    pFunc = PyDict_GetItemString(pDict, (char*)"add");

    /* build args */
 
    // pArgs = PyTuple_New(2);
    // PyTuple_SetItem(pArgs,0, PyLong_FromLong(3));
    // PyTuple_SetItem(pArgs,1, PyLong_FromLong(3));

    PyObject *pArgs1 = Py_BuildValue("i", a);
    PyObject *pArgs2 = Py_BuildValue("i", b);




    /* call */
    if(pFunc != NULL) {  
        // pValue = PyObject_CallObject(pFunc, pArgs);
        pValue = PyObject_CallFunction(pFunc, "OO",pArgs1,pArgs2 );

        
    }

    int res = PyInt_AsLong(pValue);

    return res;

}



int main(int argc, char *argv[])
{

    
    
    // Py_Initialize();
    // import_array();
    init_ar();
    char str[] = "Python";
    Py_SetProgramName(str);
    if(!Py_IsInitialized())
        cout << "init faild/n" << endl;
    // 下面可以只是方便调试，可以不用。
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('../python')");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("print os.getcwd()");
    PyRun_SimpleString("print ('Hello Python!')\n");
    
   
    int a = 10;
    int b = 20;
    int c = add(a,b);
    cout<<a<<"+"<<b<<"="<<c<<endl;


    return 0;
}










