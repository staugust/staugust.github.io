# How to debug projects with Intellij while its dependent packages' scope are provided? 

As maven references infers, `provided` scope means that you expect the JDK or a container to provide the dependency at runtime. 
Think of it with IDE situations, when compiling & packaging your project, it would download those dependent packages, then compile & package, just as you are using maven command line. 
When it comes to `Debug/Run`, things become a little different. You must provide those packages with scope `provided`, and add it to `classpath`. 

Things become clear, when we want to `Debug/Run` projects that have `provided` dependent packages, we have to make sure those dependent packages are in `classpath`. 
Here's a trick to do such thing in Intellij: 

1. Press __F4__, or click on toolbar *File -> 'Project Structure'*
2. click *Libraries -> 'New Project Library' -> 'Java'*
3. Select all jars that should be provided, and name it `localJars`
4. add `localJars` to modules' Dependencies, and set scope to `Runtime`. 

Now, enjoy it. 

# Reference 
1. https://intellij-support.jetbrains.com/hc/en-us/community/posts/206154389-How-Is-The-Maven-Provided-Scope-Supposed-To-Work-When-Run-From-IDEA-
