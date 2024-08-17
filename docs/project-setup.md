## Bootstrapping F´

> Note: if you have followed the [HelloWorld tutorial](https://fprime-community.github.io/fprime-tutorial-hello-world/) previously, this should feel very familiar...

An F´ project ties to a specific version of tools to work with F´. In order to create
this project and install the correct version of tools, you should perform a bootstrap of F´.

To do this you should follow the following steps from the [F´ installation guide](https://nasa.github.io/fprime/INSTALL.html):

1. Ensure you meet the [F´ System Requirements](https://nasa.github.io/fprime/INSTALL.html#requirements)
2. [Bootstrap your F´ project](https://nasa.github.io/fprime/INSTALL.html#creating-a-new-f-project) with the name `MathProject`

Bootstrapping your F´ project created a folder called `MathProject` (or any name you chose) containing the standard F´ project structure as well as the virtual environment up containing the tools to work with F´.


## Building the New F´ Project

The next step is to set up and build the newly created project. This will serve as a build environment for any newly
created components, and will build the F´ framework supplied components.

```bash
cd MathProject
fprime-util generate
fprime-util build -j4
```

> `fprime-util generate` sets up the build environment for a project/deployment. It only needs to be done once. At the
> end of this tutorial, a new deployment will be created and `fprime-util generate` will also be used then.

## Summary

A new project has been created with the name `MathProject` and has been placed in a new folder called in `MathProject` in
the current directory. It includes the initial build system setup, and F´ version. It is still empty in that the user
will still need to create components and deployments.

For the remainder of this Getting Started tutorial we should use the tools installed for our project and issue commands
within this new project's folder. Change into the project directory and load the newly install tools with:

```bash
cd MathProject
. fprime-venv/bin/activate
```

**Next:** [Defining Types](./defining-types.md)