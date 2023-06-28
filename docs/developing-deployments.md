# Developing Deployments

## Background 
The deployment is the portion of F' that will actually run on the spacecraft. Think of the deployment like an executable. 

## In this Section

In this section, you will create a deployment and integrate the deployment with the other work you have completed. At the end of this section, you will run the F' ground data system and test your components by actually running them! 


## Create a Deployment
Use the following command to create the deployment: 

```shell 
# In: MathProject 
fprime-util new --deployment
```

When creating the deplyoment you will be asked two questions, answer them as follows: 

```shell
[INFO] Cookiecutter: using builtin template for new deployment
deployment_name [MyDeployment]: MathDeployment
[INFO] Found CMake file at 'fprime-tutorial-math-component/project.cmake'
Add component Deployment to fprime-tutorial-math-component/project.cmake at end of file (yes/no)? yes
```

Test the build to make sure everything is okay:

```shell
# In: /MathDeployment
fprime-util generate 
fprime-util build
```


## Add Component Instances to the Deployment
Create an instance for `MathSender` in `instances.fpp`. 

```fpp 
# In: MathDeployment/Top/instances.fpp 
# Under: Active component instances 
instance mathSender: MathModule.MathSender base id 0xE00 \
  queue size Default.QUEUE_SIZE \
  stack size Default.STACK_SIZE \
  priority 100

# Under: Queued component instances 
instance mathReceiver: MathModule.MathReceiver base id 0x2700 \
  queue size Default.QUEUE_SIZE
```

## Explanation

For the `MathSender` you defined the queue size, stack size,
and thread priority. The default queue and stack sizes were used above.

The `MathReceiver was implemented with base identifier 0x2700 and the default queue size.

## Update the Topology 

Add the instances you created to `topology.fpp`. 


```fpp 
# In: MathDeployment/Top/topology.fpp 
# Under: Instances used in the topology
instance mathSender
instance mathReceiver 
```

> This step highlights the importants of capitalization. The easiest way to differentiate between the component definition and instance is the capitalization.

## Explanation 
This code defines an instance `mathSender` of component
`MathSender`. It has **base identifier** 0xE00.
FPP adds the base identifier to each the relative identifier
defined in the component to compute the corresponding
identifier for the instance.
For example, component `MathSender` has a telemetry channel
`MathOp` with identifier 1, so instance `mathSender`
has a command `MathOp` with identifier 0xE01.

## Add Packets 

Add packets for MathSender and MathReceiver in MathDeploymentPackets.xml

```xml 
<!-- In: Top/MathDeploymentPackets.xml -->
<!-- Above: Ignored packets -->
<packet name="MathSender" id="21" level="3">
    <channel name = "mathSender.VAL1"/>
    <channel name = "mathSender.OP"/>
    <channel name = "mathSender.VAL2"/>
    <channel name = "mathSender.RESULT"/>
</packet>
<packet name="MathReceiver" id="22" level="3">
    <channel name = "mathReceiver.OPERATION"/>
    <channel name = "mathReceiver.FACTOR"/>
</packet>
```

## Explanation 
These lines describe the packet definitions for the `mathSender` and `mathReceiver` telemetry channels.

## Check the Build
Just to be safe, check the build after this step.

```shell
# In: /MathDeployment
fprime-util build
```

## Check for Unconnected Ports
Check to make sure all of the ports have been connected: 

```shell 
# In: MathDeployment/Top
fprime-util fpp-check -u unconnected.txt
cat unconnected.txt 
```

At this point in time, several `mathSender` and `mathReceiver` functions (such as `mathOpIn` or `schedIn`) should still be not connected. Hence, they should appear on this list. 

Go into `topology.fpp`, connect `mathReceiver.schedIn` to rate group one using the code below:  

```fpp 
# In: Top/topology.fpp 
# Under: connections Deplyoment
rateGroup1.RateGroupMemberOut[3] -> mathReceiver.schedIn
```

> Note: `[3]` is the next available index in rate group one.

## Explanation
This line adds the connection that drives the `schedIn`
port of the `mathReceiver` component instance.

Verify that you succesfully took a port off the list of unconnected ports. 

Add the connections between the mathSender and mathReceiver

```fpp 
# In: Top/topology.fpp 
# Under: connections Deplyoment 
mathSender.mathOpOut -> mathReceiver.mathOpIn
mathReceiver.mathResultOut -> mathSender.mathResultIn
```

## Test and Run

Verify that none of the math ports are unconnected 

Go into MathDeploymentTopology.cpp and uncomment `loadParameters();`. Doing so will prevent an error in operation of F' GDS.  

```cpp
// In: MathDeploymentTopology.cpp
// Under: namespace MathDeployment{
loadParameters();
```


Now it is time to build the entire project. Navigate to `MathProject` and build:

```shell 
# In: MathProject 
fprime-util build 
```

Run the MathComponent Tutorial

```shell 
# In: MathProject 
fprime-gds 
```
> If you encounter an error on this step, try running `fprime-gds` in the `MathProject`. 

## Send Some Commands
Under Commanding there is a dropdown menu called "mnemonic". Click Mnemonic and find mathSender.DO_MATH. When you select DO_MATH, three new option should appear. In put 7 into val1, put 6 into val2, and put MUL into op. Press send command. Nothing exciting will happen, navivate to events (top left) and find the results of your command. You should see The Ultimate Answer to Life, the Universe, and Everything. 


## Summary

In this section of the tutorial, you created a deployment. While at it, you filled out the projects instance and topology. These steps are what turn a bunch hard worked code into flight-software. Further more, you ran the software! 

## Congratulations 

You have completed your F' deployment!!! If you wish to stop here, you may! You can also rest assured knowing that the work you have done is referencable. In otherwords, you've written code in the same way that you will write code for actual spacecrafts. Except... actual spacecrafts will make extensive use of unit tests and error handling. Keep going in this tutorial to learn more about unit testing, error handling, and just to practice using F'.

**Next:** [Crafting Unit Tests 1](./writing-unit-tests-1.md)