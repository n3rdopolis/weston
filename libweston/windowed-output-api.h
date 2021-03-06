/*
 * Copyright © 2016 Armin Krezović
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef WESTON_WINDOWED_OUTPUT_API_H
#define WESTON_WINDOWED_OUTPUT_API_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "plugin-registry.h"

struct weston_compositor;
struct weston_output;

#define WESTON_WINDOWED_OUTPUT_API_NAME "weston_windowed_output_api_v1"

struct weston_windowed_output_api {
	/** Assign a given width and height to an output.
	 *
	 * \param output An output to be configured.
	 * \param width  Desired width of the output.
	 * \param height Desired height of the output.
	 *
	 * Returns 0 on success, -1 on failure.
	 *
	 * This assigns a desired width and height to a windowed
         * output. The backend decides what should be done and applies
	 * the desired configuration. After using this function and
	 * generic weston_output_set_*, a windowed
	 * output should be in a state where weston_output_enable()
	 * can be run.
	 */
	int (*output_set_size)(struct weston_output *output,
			       int width, int height);

	/** Create a new windowed output.
	 *
	 * \param compositor The compositor instance.
	 * \param name       Desired name for a new output.
	 *
	 * Returns 0 on success, -1 on failure.
	 *
	 * This creates a new output in the backend using this API.
	 * After this function is ran, the created output should be
	 * ready for configuration using the output_configure() and
	 * weston_output_set_{scale,transform}().
	 *
	 * An optional name can be assigned to it, so it can be used
	 * by compositor to configure it. It can't be NULL.
	 */
	int (*output_create)(struct weston_compositor *compositor,
			     const char *name);
};

static inline const struct weston_windowed_output_api *
weston_windowed_output_get_api(struct weston_compositor *compositor)
{
	const void *api;
	api = weston_plugin_api_get(compositor, WESTON_WINDOWED_OUTPUT_API_NAME,
				    sizeof(struct weston_windowed_output_api));

	return (const struct weston_windowed_output_api *)api;
}

#ifdef  __cplusplus
}
#endif

#endif /* WESTON_WINDOWED_OUTPUT_API_H */
