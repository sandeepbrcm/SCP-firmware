/*
 * Arm SCP/MCP Software
 * Copyright (c) 2015-2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *    Thread definitions.
 */

#ifndef FWK_THREAD_H
#define FWK_THREAD_H

#include <fwk_event.h>

#include <stdint.h>

/*!
 * \addtogroup GroupLibFramework Framework
 * @{
 */

/*!
 * \defgroup GroupThread Threading
 *
 * @{
 */

/*!
 * \brief Put an event in one of the event queues.
 *
 * \details The framework copies the event description into its internal data
 *      and so does not keep track of the pointer passed as a parameter.
 *
 *      If the function is called from a thread the event is put into the
 *      targeted thread queue. Furthermore, in the runtime phase, the source
 *      identifier of the event is populated with the identifier of the caller,
 *      and it is therefore unnecessary for the caller to do so manually. Note
 *      that this does not occur in the pre-runtime phase.
 *
 *      If the function is called from an ISR, the event is put in the ISR
 *      event queue.
 *
 *      In both cases, the event identifier and target identifier are checked
 *      to be valid and to refer to the same module.
 *
 *      In the case of a delayed response event, the event's 'is_response' flag
 *      must be set.
 *
 *      If multi-threading is enabled, and \p event is a delayed response, the
 *      \ref fwk_event.cookie field of \p event must match that of the event
 *      it is responding to.
 *
 * \param[in] event Pointer to the event to queue. Must not be \c NULL.
 *
 * \retval ::FWK_SUCCESS The event was queued.
 * \retval ::FWK_E_INIT The thread framework component is not initialized.
 * \retval ::FWK_E_PARAM One or more parameters were invalid.
 * \retval ::FWK_E_PARAM One or more fields in the \p event parameter were
 *      invalid.
 * \retval ::FWK_E_OS Operating system error.
 *
 * \return Status code representing the result of the operation.
 */
int fwk_thread_put_event(struct fwk_event *event);

/*!
 * \brief Get a copy of a delayed response event.
 *
 * \details When a module or element delays a response as part of the processing
 *      of an event requiring a response, the framework automatically stores the
 *      delayed response as part of the module or element data internal to the
 *      framework. This function allows to get a copy of such delayed response
 *      event. The event is not removed from the module or element internal
 *      data.
 *
 * \param[in] id Identifier of the module or element that delayed the response.
 * \param[in] cookie Cookie of the event which the response has been delayed
 *      for. The cookie identifies the response event among the response events
 *      the entity \p id may have delayed.
 * \param[out] event The copy of the response event.
 *
 * \retval ::FWK_SUCCESS The event was queued.
 * \retval ::FWK_E_PARAM One or more parameters were invalid.
 * \retval ::FWK_E_ACCESS Access violation due to call from interrupt handler.
 *
 * \return Status code representing the result of the operation.
 */
int fwk_thread_get_delayed_response(fwk_id_t id, uint32_t cookie,
                                    struct fwk_event *event);

/*!
 * @}
 */

/*!
 * @}
 */

#endif /* FWK_THREAD_H */
