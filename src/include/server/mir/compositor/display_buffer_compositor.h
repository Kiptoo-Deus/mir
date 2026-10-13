/*
 * Copyright © Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 or 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_COMPOSITOR_DISPLAY_BUFFER_COMPOSITOR_H_
#define MIR_COMPOSITOR_DISPLAY_BUFFER_COMPOSITOR_H_

#include <mir/compositor/scene.h>

namespace mir
{
namespace compositor
{

/**
 * Whether a composition attempt may use direct presentation.
 */
enum class CompositionMode
{
    normal,    ///< Direct presentation (bypass / overlays / planes) is allowed
    recovery,  ///< Render the complete scene through the renderer; no direct presentation
};

/**
 * What a call to DisplayBufferCompositor::composite() produced.
 */
enum class CompositionResult
{
    skipped,     ///< Nothing was submitted to the sink; no post is needed
    direct,      ///< Sink content uses direct presentation (bypass / overlay)
    composited,  ///< The complete visible scene was rendered into one image
};

class DisplayBufferCompositor
{
public:
    virtual ~DisplayBufferCompositor() = default;

    /// Returns the kind of frame produced.
    virtual CompositionResult composite(
        SceneElementSequence&& scene_sequence,
        CompositionMode mode) = 0;

protected:
    DisplayBufferCompositor() = default;
    DisplayBufferCompositor& operator=(DisplayBufferCompositor const&) = delete;
    DisplayBufferCompositor(DisplayBufferCompositor const&) = delete;
};

}
}

#endif /* MIR_COMPOSITOR_DISPLAY_BUFFER_COMPOSITOR_H_ */
