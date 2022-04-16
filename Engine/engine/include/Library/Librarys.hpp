#pragma once

#include <d3d12.h>
#include "d3dx12.h"
#include <d3d12shader.h>
#include <dxgi1_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxcompiler.lib")

namespace engine {

	// using namespace DirectX;
	// using namespace Microsoft::WRL;

	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	// DXGI
	using DXGIFactory3          = Microsoft::WRL::ComPtr<IDXGIFactory3>;
	using DXGIAdapter           = Microsoft::WRL::ComPtr<IDXGIAdapter1>;
	using DXGIOutput            = Microsoft::WRL::ComPtr<IDXGIOutput>;
	using DXGISwapChain3        = Microsoft::WRL::ComPtr<IDXGISwapChain3>;

	// DirectX12
	using D3D12Device           = Microsoft::WRL::ComPtr<ID3D12Device>;
	using D3D12CommandQueue     = Microsoft::WRL::ComPtr<ID3D12CommandQueue>;
	using D3D12CommandAllocator = Microsoft::WRL::ComPtr<ID3D12CommandAllocator>;
	using D3D12CommandList      = Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>;
	using D3D12RootSignature    = Microsoft::WRL::ComPtr<ID3D12RootSignature>;
	using D3D12PipelineState    = Microsoft::WRL::ComPtr<ID3D12PipelineState>;
	using D3D12Fence            = Microsoft::WRL::ComPtr<ID3D12Fence>;
	using D3D12DescriptorHeap   = Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>;
	using D3D12Resource         = Microsoft::WRL::ComPtr<ID3D12Resource>;

	using D3DBlob               = Microsoft::WRL::ComPtr<ID3DBlob>;

}