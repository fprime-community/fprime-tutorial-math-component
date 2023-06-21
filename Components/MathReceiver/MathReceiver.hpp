// ======================================================================
// \title  MathReceiver.hpp
// \author asloan
// \brief  hpp file for MathReceiver component implementation class
// ======================================================================

#ifndef MathReceiver_HPP
#define MathReceiver_HPP

#include "Components/MathReceiver/MathReceiverComponentAc.hpp"

namespace MathModule {

  class MathReceiver :
    public MathReceiverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object MathReceiver
      //!
      MathReceiver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object MathReceiver
      //!
      ~MathReceiver();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------
      void parameterUpdated(FwPrmIdType id);
      //! Handler implementation for mathOpIn
      //!
      void mathOpIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 val1, /*!< 
      The first operand
      */
          const MathModule::MathOp &op, /*!< 
      The operation
      */
          F32 val2 /*!< 
      The second operand
      */
      );

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< 
      The call order
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for CLEAR_EVENT_THROTTLE command handler
      //! Clear the event throttle
      void CLEAR_EVENT_THROTTLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    PRIVATE:
      // ----------------------------------------------------------------------
      // Member variables 
      // ---------------------------------------------------------------------- 
    U32 numMathOps; 

    };

} // end namespace MathModule

#endif
