#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image& picture) {
    basePicture = picture; // Deep copy of the base picture
    stickerLayers.clear(); // Initialize the sticker layers vector
}

int StickerSheet::addSticker(Image& sticker, int x, int y) {
    // Find the lowest available layer
    for (size_t i = 0; i < stickerLayers.size(); ++i) {
        if (!stickerLayers[i].isOccupied) {
            stickerLayers[i].sticker = &sticker;
            stickerLayers[i].x = x;
            stickerLayers[i].y = y;
            stickerLayers[i].isOccupied = true;
            return i; // Return the index of the layer
        }
    }
    // If no available layer, add a new one
    StickerLayer newLayer;
    newLayer.sticker = &sticker;
    newLayer.x = x;
    newLayer.y = y;
    newLayer.isOccupied = true;
    stickerLayers.push_back(newLayer);
    return stickerLayers.size() - 1; // Return the index of the new layer
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    if (layer < stickerLayers.size()) {
        // Replace existing sticker
        stickerLayers[layer].sticker = &sticker;
        stickerLayers[layer].x = x;
        stickerLayers[layer].y = y;
        stickerLayers[layer].isOccupied = true;
    } else {
        // Add new layers up to the specified layer
        stickerLayers.push_back(StickerLayer());
        stickerLayers.back().sticker = &sticker;
        stickerLayers.back().x = x;
        stickerLayers.back().y = y;
        stickerLayers.back().isOccupied = true;
        layer = stickerLayers.size() - 1; // Update layer to the new top layer
    }
    return layer; // Return the index of the layer
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index >= stickerLayers.size() || !stickerLayers[index].isOccupied) {
        return nullptr; // Invalid index or no sticker at this layer
    }
    return stickerLayers[index].sticker; // Return pointer to the sticker
}

bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickerLayers.size() || !stickerLayers[index].isOccupied) {
        return false; // Invalid index or no sticker at this layer
    }
    stickerLayers[index].x = x; // Update x coordinate
    stickerLayers[index].y = y; // Update y coordinate
    return true; // Successful translation
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < stickerLayers.size()) {
        stickerLayers[index].isOccupied = false; // Mark the layer as unoccupied
        stickerLayers[index].sticker = nullptr; // Remove the sticker reference
    }
}

int StickerSheet::layers() const {
    return stickerLayers.size(); // Return the number of layers
}

Image StickerSheet::render() const {
    // compute bounds (allow negative offsets)
    int minX = 0, minY = 0;
    int maxX = static_cast<int>(basePicture.width());
    int maxY = static_cast<int>(basePicture.height());

    for (const auto &layer : stickerLayers) {
        if (!layer.isOccupied || layer.sticker == nullptr) continue;
        int left   = layer.x;
        int top    = layer.y;
        int right  = layer.x + static_cast<int>(layer.sticker->width());
        int bottom = layer.y + static_cast<int>(layer.sticker->height());

        if (left < minX)  minX  = left;
        if (top  < minY)  minY  = top;
        if (right > maxX) maxX  = right;
        if (bottom > maxY) maxY = bottom;
    }

    // compute new canvas size
    int newWidthI  = maxX - minX;
    int newHeightI = maxY - minY;
    if (newWidthI <= 0)  newWidthI  = 0;
    if (newHeightI <= 0) newHeightI = 0;
    unsigned newWidth  = static_cast<unsigned>(newWidthI);
    unsigned newHeight = static_cast<unsigned>(newHeightI);

    // create canvas sized to contain everything
    Image result(newWidth, newHeight);

    // offsets to translate original coords into result coords
    int baseOffsetX = -minX;
    int baseOffsetY = -minY;

    // draw base picture into result at offset (-minX, -minY)
    for (unsigned bx = 0; bx < basePicture.width(); ++bx) {
        for (unsigned by = 0; by < basePicture.height(); ++by) {
            unsigned rx = static_cast<unsigned>(static_cast<int>(bx) + baseOffsetX);
            unsigned ry = static_cast<unsigned>(static_cast<int>(by) + baseOffsetY);
            result.getPixel(rx, ry) = basePicture.getPixel(bx, by);
        }
    }

    // overlay stickers (only non-transparent pixels)
    for (const auto &layer : stickerLayers) {
        if (!layer.isOccupied || layer.sticker == nullptr) continue;
        const Image *sticker = layer.sticker;
        int stickerOffsetX = layer.x - minX; // translated into result coords
        int stickerOffsetY = layer.y - minY;

        for (unsigned sx = 0; sx < sticker->width(); ++sx) {
            for (unsigned sy = 0; sy < sticker->height(); ++sy) {
                int rx_i = stickerOffsetX + static_cast<int>(sx);
                int ry_i = stickerOffsetY + static_cast<int>(sy);
                if (rx_i < 0 || ry_i < 0) continue;
                if (rx_i >= static_cast<int>(newWidth) || ry_i >= static_cast<int>(newHeight)) continue;

                const cs225::HSLAPixel &sp = sticker->getPixel(sx, sy);
                if (sp.a > 0) {
                    result.getPixel(static_cast<unsigned>(rx_i), static_cast<unsigned>(ry_i)) = sp;
                }
            }
        }
    }

    return result;
}