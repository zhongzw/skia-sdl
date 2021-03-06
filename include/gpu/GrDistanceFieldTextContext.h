/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrDistanceFieldTextContext_DEFINED
#define GrDistanceFieldTextContext_DEFINED

#include "GrTextContext.h"

class GrTextStrike;

/*
 * This class implements GrTextContext using distance field fonts
 */
class GrDistanceFieldTextContext : public GrTextContext {
public:
    GrDistanceFieldTextContext(GrContext*, const GrPaint&, const SkPaint&);
    virtual ~GrDistanceFieldTextContext();

    virtual void drawPackedGlyph(GrGlyph::PackedID, GrFixed left, GrFixed top,
                                 GrFontScaler*) SK_OVERRIDE;

    void drawText(const char text[], size_t byteLength,
                  SkScalar x, SkScalar y, SkGlyphCache*, GrFontScaler*);
    void drawPosText(const char text[], size_t byteLength,
                     const SkScalar pos[], SkScalar constY,
                     int scalarsPerPosition,
                     SkGlyphCache* cache, GrFontScaler* fontScaler);

    const SkPaint& getSkPaint() { return fSkPaint; }

private:
    GrTextStrike*           fStrike;
    SkScalar                fTextRatio;

    void flushGlyphs();                 // automatically called by destructor

    enum {
        kMinRequestedGlyphs      = 1,
        kDefaultRequestedGlyphs  = 64,
        kMinRequestedVerts       = kMinRequestedGlyphs * 4,
        kDefaultRequestedVerts   = kDefaultRequestedGlyphs * 4,
    };

    SkPaint                 fSkPaint;
    SkPoint*                fVertices;
    int32_t                 fMaxVertices;
    GrTexture*              fCurrTexture;
    int                     fCurrVertex;
};

#endif
