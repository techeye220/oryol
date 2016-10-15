#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::TextureSetup
    @ingroup Gfx
    @brief setup object for textures and render targets
*/
#include "Resource/Locator.h"
#include "Resource/Id.h"
#include "Gfx/Core/Enums.h"
#include "Gfx/Core/GfxConfig.h"
#include "Gfx/Core/SamplerState.h"
#include "Gfx/Attrs/ImageDataAttrs.h"

namespace Oryol {
    
class TextureSetup {
public:
    /// default constructor (workaround for gcc)
    TextureSetup() { };
    /// asynchronously load from file
    static TextureSetup FromFile(const Locator& loc, Id placeholder=Id::InvalidId());
    /// asynchronously load from file
    static TextureSetup FromFile(const Locator& loc, const TextureSetup& blueprint=TextureSetup(), Id placeholder=Id::InvalidId());
    /// setup texture from raw pixel data
    static TextureSetup FromPixelData(int w, int h, int numMipMaps, TextureType::Code type, PixelFormat::Code fmt, const TextureSetup& blueprint=TextureSetup());
    /// setup empty 2D or Cube texture (usually for dynamic streaming of CPU generated texture data)
    static TextureSetup Empty(int w, int h, int numMipMaps, TextureType::Code type, PixelFormat::Code fmt, Usage::Code usage);
    /// setup empty 3D texture
    static TextureSetup Empty3D(int w, int h, int d, int numMipMaps, PixelFormat::Code fmt, Usage::Code usage);
    /// setup empty array texture
    static TextureSetup EmptyArray(int w, int h, int slices, int numMipMaps, PixelFormat::Code, Usage::Code usage);
    /// setup as absolute-size render target
    static TextureSetup RenderTarget(int w, int h);

    /// return true if texture should be setup from a file
    bool ShouldSetupFromFile() const;
    /// return true if texture should be setup from raw pixel data
    bool ShouldSetupFromPixelData() const;
    /// return true if texture should be created empty
    bool ShouldSetupEmpty() const;
    /// return true if texture should be setup as render target
    bool ShouldSetupAsRenderTarget() const;
    /// return true if render target has depth
    bool HasDepth() const;

    /// intended usage
    Usage::Code TextureUsage = Usage::Immutable;
    /// texture type
    TextureType::Code Type = TextureType::Texture2D;
    /// width in pixels
    int Width = 0;
    /// height in pixels
    int Height = 0;
    /// depth/slices in pixels (for 3D and Array textures)
    int Depth = 0;
    /// number of mipmaps (default is 1, only for FromPixelData)
    int NumMipMaps = 1;
    /// the color pixel format
    PixelFormat::Code ColorFormat = PixelFormat::RGBA8;
    /// the depth pixel format (only if render target, PixelFormat::None if render target should not have depth buffer)
    PixelFormat::Code DepthFormat = PixelFormat::None;
    /// MSAA samples (2, 4, 8... no MSAA: 1), check MSAARenderTargets feature availability!
    int SampleCount = 1;

    /// sampler state
    SamplerState Sampler;

    /// resource locator
    class Locator Locator = Locator::NonShared();
    /// resource placeholder
    Id Placeholder;

    /// optional image surface offsets and sizes
    ImageDataAttrs ImageData;

private:
    bool setupFromFile = false;
    bool setupFromPixelData = false;
    bool setupEmpty = false;
    bool setupAsRenderTarget = false;
    bool hasMipMaps = false;
};
    
} // namespace Oryol
