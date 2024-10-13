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

This command will ask for some input. Respond with the following answers:

```
  Deployment name (MyDeployment): MathDeployment
```

> For any other questions, select the default response.

Test the build to make sure everything is okay:

```shell
# In MathProject/MathDeployment
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

This code defines an instance `mathSender` of component `MathSender`. It has base identifier 0xE00. FPP adds the base identifier to each the relative identifier defined in the component to compute the corresponding identifier for the instance. For example, component MathSender has a telemetry channel MathOp with identifier 1, so instance mathSender has a command MathOp with identifier 0xE01

The `mathReceiver` was defined with base identifier 0x2700 and the default queue size.

## Update the Topology 

Add the instances you created to `topology.fpp`. 

```fpp 
# In: MathDeployment/Top/topology.fpp 
# Under: Instances used in the topology
instance mathSender
instance mathReceiver 
```

> This step highlights the importance of capitalization. The easiest way to differentiate between the component definition and instance is the capitalization.

## Explanation 

These lines add the mathSender and mathReceiver instances to the topology.

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
# In: MathProject/MathDeployment
fprime-util build
```

## Check for Unconnected Ports
Check to make sure all of the ports have been connected: 

```shell 
# In: MathDeployment/Top
fprime-util fpp-check -u unconnected.txt
cat unconnected.txt 
```

At this point in time, several `mathSender` and `mathReceiver` ports (such as `mathOpIn` or `schedIn`) are still unconnected. Hence, they should appear on this list. 

Go into `topology.fpp`, connect `mathReceiver.schedIn` to rate group one using the code below:  

```fpp 
# In: Top/topology.fpp 
# Under: connections RateGroups for rateGroup1
rateGroup1.RateGroupMemberOut[3] -> mathReceiver.schedIn
```

> Note: `[3]` is the next available index in rate group one.

## Explanation
This line adds the connection that drives the `schedIn` port of the `mathReceiver` component instance.

Verify that you successfully took a port off the list of unconnected ports. 

Add the connections between the mathSender and mathReceiver

```fpp 
# In: Top/topology.fpp 
# Under: connections MathDeployment 
mathSender.mathOpOut -> mathReceiver.mathOpIn
mathReceiver.mathResultOut -> mathSender.mathResultIn
```

## Test and Run

**Re-run the check for unconnected ports**: Notice that no mathSender or mathReceiver ports are unconnected. 

Go into MathDeploymentTopology.cpp and uncomment `loadParameters();`. This function is commented by default because it does not exist when the model has no parameters. Since we defined a parameter in `MathReceiver`, we shall call the function.

```cpp
// In: MathDeploymentTopology.cpp
// Under: namespace MathDeployment{
loadParameters();
```


Now it is time to build the entire project and run it! Navigate back to `MathDeployment` and build:

```shell 
# In: MathProject/MathDeployment
fprime-util build 
```

Run the MathComponent deployment through the GDS:

```shell 
# In: MathProject/MathDeployment
fprime-gds 
```
> If you encounter an error on this step, try running `fprime-gds` in the `MathProject`. 

## Send Some Commands
Under _Commanding_ there is a drop-down menu called "mnemonic". Click Mnemonic and find mathSender.DO_MATH. When you select DO_MATH, three new option should appear. In put 7 into val1, put 6 into val2, and put MUL into op. Press send command. Navigate to _Events_ (top left) and find the results of your command. You should see The Ultimate Answer to Life, the Universe, and Everything: 42.

For a more detailed guide to the F´ GDS, see the [GDS Introduction Guide](https://nasa.github.io/fprime/UsersGuide/gds/gds-introduction.html).


## Summary

In this section of the tutorial, you created a deployment. While at it, you filled out the projects instance and topology. These steps are what turn a bunch hard worked code into flight-software. Further more, you ran the software! 

## Congratulations 

You have completed your F' deployment! If you wish to stop here, you may. You can also rest assured knowing that the work you have done is reusable. In other words, you've written code in the same way that you will write code for actual spacecrafts. Except... actual spacecrafts will make extensive use of unit tests and error handling. Keep going in this tutorial to learn more about unit testing, error handling, and just to practice using F'.

**Next:** [Writing Unit Tests Part 1: Creating the Implementation Stub](./writing-unit-tests-1.md)
