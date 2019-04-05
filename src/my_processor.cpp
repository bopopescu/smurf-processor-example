#include <smurf_processor.h>

namespace bp = boost::python;

class MyProcessor : public SmurfProcessor
{
public:
    void transmit(smurf_tx_data_t* data)
    {
        printf("   :::  My custom processor  :::   \n");
        printf("SMuRF hearder received:\n");
        for (int i = 0; i < smurfheaderlength; ++i)
          printf(" - byte[%03d] = 0x%02x\n", i, data[i]);
        printf("\n");
    };

    static void setup_python()
      {
        bp::class_<MyProcessor, boost::shared_ptr<MyProcessor>, bp::bases<ris::Slave>, boost::noncopyable >("MyProcessor",bp::init<>())
          .def("printTransmitStatistic", &MyProcessor::printTransmitStatistic)
        ;

        bp::implicitly_convertible<boost::shared_ptr<MyProcessor>, ris::SlavePtr>();
      };
};

BOOST_PYTHON_MODULE(MyModule)
{
  PyEval_InitThreads();

  try
  {
    MyProcessor::setup_python();
  }
  catch (...)
  {
    printf("Failed to load my processor module. import rogue first\n");
  }

  printf("Loaded my processor module\n");
};