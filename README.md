# hlsl-demo
This is a small Deferred Rendering Pipeline C++/HLSL demo I whipped up within 2 weeks. 
It contains a simple scene made with cubes and a single rock material. 
I put in 1 light only for now for aesthetic reasons, but it can support an unlimited amount.
A lot was cut for time, given that I assumed to have only 2 weeks to do this, but nice to have features would be:
- .obj loader instead of those cubes
- Spot shadows that have a circular shape
- Post processing effects, such as Bloom and Ambient Occlusion
I will continue working on this project at a slower pace, as it seems like a nice little demo.

To navigate the demo from the branch, run DirectXDemo.exe. 
While in the program, arrows crudely move the camera while 1-7 switches between the following stages in the pipeline:
- 1 - Final result
- 2 - Scene color
- 3 - Scene normals
- 4 - Scene world position
- 5 - Light depth view (used for shadow computations)
- 6 - Total scene diffuse lighting
- 7 - Total scene specular lighting
