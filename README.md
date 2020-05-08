# Weiss

> Weiss II is cross-platform, api-agnostic and header-only rendering engine built with c++17. It is intended to be a wrapper around low-level apis to make the developpement of 2D and 3D applications simpler and faster.

## Current Support

| Icon    | :heavy_check_mark:         | :x:                   | :warning:         | :small_red_triangle: |
| ------- | -------------------------- | --------------------- | ----------------- | -------------------- |
| Meaning | Fully Integrated & Working | Haven't Started (yet) | Being Implemented | Triangle Rendering   |

| Render API | Status                            | Operating System | Status             |
| ---------- | --------------------------------- | ---------------- | ------------------ |
| DirectX 11 | :warning: (:small_red_triangle:)  | Windows          | :heavy_check_mark: |
| DirectX 12 | :warning: (:small_red_triangle:)  | Linux            | :x:                |
| OpenGL     | :x:                               | Mac OSX          | :x:                |
| Vulkan     | :warning:                         | | |

## Getting Started

Dependencies :

+ Install the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)
+ Download the [d3dx12.h file](https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/Libraries/D3DX12/d3dx12.h) from microsoft's official github
+ Install [GLAD](https://glad.dav1d.de/) for OpenGL
+ Download & Install the [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

Building :

+ Clone the repository with [Git](https://git-scm.com/)

  ```git clone https://github.com/PolarToCartesian/Weiss-II```

+ Setup the following directories :
  + Library Directories
    + VulkanSDK/Lib   (for x64)
    + VulkanSDK/Lib32 (for x86)
  + Include Directories
    + VulkanSDK/Include
    + Glad/include
    + d3dx12.h file's directory

## Test Code

This code should run without any errors and show a colored triangle using directx11.

<details>
  <summary>Main.cpp</summary>


```c++
#include "Weiss-II/Include.h"

struct Vertex {
	Vec3f position;
	Vec3f color;
};

int main() {
	ENABLE_CONSOLE();

	try {
		WindowHandle    window    = Window::Create({1920u, 1080u});
		RenderAPIHandle renderAPI = RenderAPI::Create(RenderAPIName::DIRECTX11);

		std::vector<RenderPipelineDesc> pipelineDescs{
			RenderPipelineDesc{"vs.hlsl", {
				{ "POSITION", ShaderInputElementType::VECTOR_3D_FLOAT_32 },
				{ "COLOR",    ShaderInputElementType::VECTOR_3D_FLOAT_32 }
			}, "ps.hlsl", { 0u }, PrimitiveTopology::TRIANGLES}
		};

		renderAPI->InitRenderAPI(window);

		renderAPI->InitPipelines(pipelineDescs);

		std::array<Vertex, 3u> vertices{
			Vertex{Vec3f{+0.0f, +1.0f, 0.5f}, Vec3f{1.0f, 0.0f, 0.0f}},
			Vertex{Vec3f{+1.0f, -1.0f, 0.5f}, Vec3f{0.0f, 1.0f, 0.0f}},
			Vertex{Vec3f{-1.0f, -1.0f, 0.5f}, Vec3f{0.0f, 0.0f, 1.0f}},
		};

		std::array<uint32_t, 3u> indices{ 0u, 1u, 2u };

		Drawable drawable{
			0u,
			renderAPI->CreateVertexBuffer(vertices.size(), sizeof(Vertex)),
			renderAPI->CreateIndexBuffer(indices.size())
		};

		renderAPI->GetVertexBuffer(drawable.vertexBufferIndex).Set(vertices);
		renderAPI->GetIndexBuffer(drawable.indexBufferIndex.value()).Set(indices);

		while (window->IsRunning()) {
			window->Update();

			cam.HandleKeyboardInputs(window->GetKeyboard(), 0.1f, 'W', 'S', 'A', 'D', VK_SPACE, VK_SHIFT);
			renderAPI->GetVertexBuffer(drawable.vertexBufferIndex).Update();
			renderAPI->GetIndexBuffer(drawable.indexBufferIndex.value()).Update();
			cam.CalculateTransform();

			renderAPI->BeginDrawing();
			renderAPI->Draw(drawable, indices.size());
			renderAPI->EndDrawing();
			
			renderAPI->Present(false);
		}
	} catch (const std::runtime_error& e) {
		std::cout << e.what() << '\n';
	}
}
```
</details>

---

<details>
  <summary>vs.hlsl</summary>

```hlsl
struct VSOUT
{
    float4 out_position : SV_POSITION;
    float4 out_color : COLOR;
};

VSOUT main(float3 position : POSITION, float3 color : COLOR)
{
    VSOUT _out;
    _out.out_position = float4(position, 1.0f);
    _out.out_color = float4(color, 1.0f);

    return _out;
}
```
</details>

---

<details>
  <summary>ps.hlsl</summary>

```hlsl
float4 main(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    return color;
}
```
</details>
