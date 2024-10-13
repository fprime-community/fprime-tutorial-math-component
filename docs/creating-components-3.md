# Creating Components Part 3: Starting the MathReceiver

## In this Section 

In this section you will begin creating `MathReceiver` following the same steps as the last section. Note, that the `MathReceiver` is a little different than the `MathSender`.

## Component Description

The `MathReceiver` is a queued component which receives parameters, sends parameters, logs events, and sends telemetry. With this is mind, use the following command to create the `MathReceiver` component. 

## Creating the MathReceiver

```shell
# In: Components
fprime-util new --component 
```
This command will prompt you for some inputs. You should specify the follow so that the components matches the short description above. Don't forget that this is a QUEUED component:

```
[INFO] Cookiecutter source: using builtin
Component name [MyComponent]: MathReceiver 
Component short description [Example Component for F Prime FSW framework.]: Your description
Component namespace [Component]: MathModule
Select component kind:
1 - active
2 - passive
3 - queued
Choose from 1, 2, 3 [1]: 3 
Enable Commands?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Telemetry?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Events?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
Enable Parameters?:
1 - yes
2 - no
Choose from 1, 2 [1]: 1
[INFO] Found CMake file at 'MathProject/project.cmake'
Add component Components/MathSender to MathProject/project.cmake at end of file (yes/no)? yes
Generate implementation files (yes/no)? yes
```

Before doing anything to the files you have just generated, try building:

```shell 
# In: MathReceiver
fprime-util build
```

## Editing the F Prime Prime Model 
Now that you have created the component, you can implement the component behavior in the fpp model. Use a text editor to entirely replace the existing `MathReceiver.fpp` with the following: 

```fpp
# In: MathReceiver.fpp
module MathModule {

  @ Component for receiving and performing a math operation
  queued component MathReceiver {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for receiving the math operation
    async input port mathOpIn: OpRequest

    @ Port for returning the math result
    output port mathResultOut: MathResult

    @ The rate group scheduler input
    sync input port schedIn: Svc.Sched

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive
    command recv port cmdIn

    @ Command registration
    command reg port cmdRegOut

    @ Command response
    command resp port cmdResponseOut

    @ Event
    event port eventOut

    @ Parameter get
    param get port prmGetOut

    @ Parameter set
    param set port prmSetOut

    @ Telemetry
    telemetry port tlmOut

    @ Text event
    text event port textEventOut

    @ Time get
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Parameters
    # ----------------------------------------------------------------------

    @ The multiplier in the math operation
    param FACTOR: F32 default 1.0 id 0 \
      set opcode 10 \
      save opcode 11

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Factor updated
    event FACTOR_UPDATED(
                          val: F32 @< The factor value
                        ) \
      severity activity high \
      id 0 \
      format "Factor updated to {f}" \
      throttle 3

    @ Math operation performed
    event OPERATION_PERFORMED(
                               val: MathOp @< The operation
                             ) \
      severity activity high \
      id 1 \
      format "{} operation performed"

    @ Event throttle cleared
    event THROTTLE_CLEARED \
      severity activity high \
      id 2 \
      format "Event throttle cleared"

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Clear the event throttle
    async command CLEAR_EVENT_THROTTLE \
      opcode 0

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The operation
    telemetry OPERATION: MathOp id 0

    @ Multiplication factor
    telemetry FACTOR: F32 id 1

  }

}
```

## Explanation 
This code defines a component `MathReceiver`.
The component is **queued**, which means it has a queue but no thread.
Work occurs when the thread of another component invokes the `schedIn` port of this component.

We have divided the specifiers of this component into six groups:

1. **General ports:** There are three ports:
- an input port `mathOpIn` for receiving a math operation,
`mathOpIn` is asynchronous. That means invocations of `mathOpIn` put messages on a queue.
- an output port `mathResultOut` for sending a math result, and
- an input port `schedIn` for receiving invocations from the scheduler.
`schedIn` is synchronous. That means invocations of `schedIn` immediately call the handler function to do work.

2. **Special ports:**
As before, there are special ports for commands, events, telemetry, and time. There are also special ports for getting and setting parameters. We will explain the function of these ports below.

3. **Parameters:** There is one **parameter**.
A parameter is a constant that is configurable by command. In this case there is one parameter `FACTOR`.
It has the default value 1.0 until its value is changed by command.
When doing math, the `MathReceiver` component performs the requested operation and then multiplies by this factor.
For example, if the arguments of the `mathOpIn` port are _v1_, `ADD`, and _v2_, and the factor is _f_, then the result sent on `mathResultOut` is _(v1 + v2) f_.

4. **Events:** There are three event reports:

   1. `FACTOR_UPDATED`: Emitted when the `FACTOR` parameter
      is updated by command.
      This event is **throttled** to a limit of three.
      That means that after the event is emitted three times
      it will not be emitted any more, until the throttling
      is cleared by command (see below).

   2. `OPERATION_PERFORMED`: Emitted when this component
      performs a math operation.

   3. `THROTTLE_CLEARED`: Emitted when the event throttling
      is cleared.

5. **Commands:** There is one command for clearing the event throttle.

6. **Telemetry:** There two telemetry channels: one for reporting the last operation received and one for reporting the factor parameter.

For the parameters, events, commands, and telemetry, we chose to put in all the opcodes and identifiers explicitly.
These can also be left implicit, as in the `MathSender` component example.
For more information, see the [_FPP User's Guide_](https://fprime-community.github.io/fpp/fpp-users-guide.html#Defining-Components).


## Generate the Implementation Files


Generate cpp and hpp files based off your `MathReceiver` by using: 

```shell
# In: MathReceiver 
fprime-util impl
```

Replace the original cpp and hpp files with the ones you just created:

```shell 
# In: MathReceiver
mv MathReceiver.template.cpp MathReceiver.cpp
mv MathReceiver.template.hpp MathReceiver.hpp
```

Test the build:

```shell 
# In: MathReceiver
fprime-util build 
```

## Summary
You are two thirds of the way through finishing `MathReceiver`.
So far, you have created a queued component stub, filled in the fpp 
file, and wrote component characteristics in `MathReceiver.fpp`. Next,
you will write the behavior for `MathReceiver`.

**Next:** [Creating Components Part 4: Implementing MathReceiver Behavior](./creating-components-4.md)