# Adding Telemetry

## In this Section

In this section of the tutorial, you will add a telemetry channel to report the number of math operations the `MathReceiver` has performed. 

Before reading these steps, do your best to look at the existing files in this tutorial and implement a telemetry channel on your own. 

1. Add a telemetry channel to `MathReceiver.fpp`: 

```fpp
# In: MathReceiver.fpp, under the Telemetry section
@ Number of math operations 
    telemetry NUMBER_OF_OPS: U32 
```
**Explanation:** Here you defined a telemetry channel  which you arbitrarily named `NUMBER_OF_OPS` which  carries a 32 bit unsigned integer. 

2. Add a member variable to `MathReceiver.hpp`:

```cpp
// In: MathReceiver.hpp
// Under: PRIVATE
U32 numMathOps; 
```

3. Update the constructor so that it initializes `numMathOps` to zero:

```cpp
// In: MathReceiver.cpp 
// Under: Construction, Initialization, and Destruction 
MathReceiver ::
    MathReceiver(
        const char *const compName
    ) : MathReceiverComponentBase(compName),
        numMathOps(0) 
  {

  }
```

4. Increment numMathOps: 

```cpp
// In: MathReceiver.cpp 
// Within mathOpIn_handler
numMathOps++;  
```

5. Emit telemetry: 
```cpp
// In: MathReceiver.cpp 
// Within: mathOpIn_handler
// After: numMathOps++
this->tlmWrite_NUMBER_OF_OPS(numMathOps); 
```
> Note: This function will get autocoded by FPP since we defined the telemetry channel.

6. Add the channel to the pre-existing MathReceiver packet in `MathDeploymentPackets.xml`:

```xml
    <!-- In: MathDeploymentPackets.xml -->
    <packet name="MathReceiver" id="22" level="3">
        <channel name = "mathReceiver.OPERATION"/>
        <channel name = "mathReceiver.FACTOR"/>
        <channel name = "mathReceiver.NUMBER_OF_OPS"/>  <!-- Add this line -->
    </packet>
```


7. Build and test:

```shell 
# In: MathProject
fprime-util build -j4 
fprime-gds 
```

Send a command and verify that the channel gets value 1.

Write some unit tests to prove that this channel is working. 

## Summary 

In this section you defined a telemetry channel and implemented a new variable, that will be sent through the channel.

**Next:** [Error handling 1](./error-handling-1.md)
