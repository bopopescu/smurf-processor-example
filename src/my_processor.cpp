#include <smurf_processor.h>

namespace bp = boost::python;

class MyProcessor : public SmurfProcessor
{
public:
    void transmit(SmurfPacket_RO sp)
    {
      std::cout << "=====================================" << std::endl;
      std::cout << "Packet received" << std::endl;
      std::cout << "=====================================" << std::endl;
      std::cout << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << " HEADER:" << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << "Version            = " << unsigned(sp->getVersion()) << std::endl;
      std::cout << "Crate ID           = " << unsigned(sp->getCrateID()) << std::endl;
      std::cout << "Slot number        = " << unsigned(sp->getSlotNumber()) << std::endl;
      std::cout << "Number of channels = " << unsigned(sp->getNumberChannels()) << std::endl;
      std::cout << "Unix time          = " << unsigned(sp->getUnixTime()) << std::endl;
      std::cout << "Counter 0          = " << unsigned(sp->getCounter0()) << std::endl;
      std::cout << "Counter 1          = " << unsigned(sp->getCounter1()) << std::endl;
      std::cout << "Counter 2          = " << unsigned(sp->getCounter2()) << std::endl;
      std::cout << "Frame counter      = " << unsigned(sp->getFrameCounter()) << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << " DATA (first 20 points):" << std::endl;
      std::cout << "-----------------------" << std::endl;
      for (std::size_t i(0); i < 20; ++i)
         std::cout << "Data[" << i << "] = " << sp->getValue(i) << std::endl;
      std::cout << "-----------------------" << std::endl;
      std::cout << std::endl;
      std::cout << "=====================================" << std::endl;
    };

    static void setup_python()
      {
        bp::class_<MyProcessor, boost::shared_ptr<MyProcessor>, bp::bases<ris::Slave>, boost::noncopyable >("MyProcessor",bp::init<>())
          .def("printTransmitStatistic", &MyProcessor::printTransmitStatistic)
          .def("setDebug",  &MyProcessor::setDebug)
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