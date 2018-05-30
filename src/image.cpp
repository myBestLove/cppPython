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


    

PyObject *pModule,*pFunc,*pDict;

void trans(cv::Mat image){

    /* import */
    pModule = PyImport_ImportModule("image_module");
    if (pModule == NULL) {  
        cout<<"ERROR importing module"<<endl; 
        return ; 
    } 

    pDict = PyModule_GetDict(pModule);

    pFunc = PyDict_GetItemString(pDict, (char*)"trans_image");


    PyObject  *iArgs = pbcvt::fromMatToNDArray(image);

    PyObject *pValue;
    if(pFunc != NULL) { 
        pValue = PyObject_CallFunction(pFunc, "O",iArgs );


    }


    cv::Mat trans_image = pbcvt::fromNDArrayToMat(pValue);
    imshow("a",trans_image);
    waitKey(0);
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

    cv::Mat image = cv::imread("/home/jason/code/FCRN-DepthPrediction/Images/1.jpg",0);
    
   


    trans(image);


    


    return 0;
}










