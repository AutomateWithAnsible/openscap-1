/*
 * Copyright 2009 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


/**
 * @addtogroup XCCDF_POLICY
 * @{
 * @file xccdf_policy.h
 * Open-scap XCCDF Policy library interface.
 * @author Maros Barabas <mbarabas@redhat.com>
 * @author Dave Niemoller <david.niemoller@g2-inc.com>
 */

#ifndef XCCDF_POLICY_H_
#define XCCDF_POLICY_H_

#include <stdbool.h>
#include <time.h>
#include <oscap.h>
#include <xccdf.h>
 
/**
 * @struct xccdf_policy_model
 * Handle all policies for given XCCDF benchmark
 */
struct xccdf_policy_model;

/**
 * @struct xccdf_policy
 * Policy structure that abstract benchmark's profile
 */
struct xccdf_policy;

/**
 * @struct xccdf_value_binding
 * Value bindings of policy
 */
struct xccdf_value_binding;

/**
 * @struct xccdf_policy_iterator
 * Iterate through policies
 * @see xccdf_policy_model_get_policies
 */
struct xccdf_policy_iterator;

/************************************************************/

/**
 * Constructor of Policy Model structure
 * @param benchmark Struct xccdf_benchmark with benchmark model
 * @return new xccdf_policy_model
 * @memberof xccdf_policy_model
 */
struct xccdf_policy_model *xccdf_policy_model_new(struct xccdf_benchmark *benchmark);

/**
 * Constructor of Policy structure
 * @param model Policy model
 * @param profile Profile from XCCDF Benchmark
 * @memberof xccdf_policy
 */
struct xccdf_policy * xccdf_policy_new(struct xccdf_policy_model * model, struct xccdf_profile * profile);

/**
 * Constructor of structure with profile bindings - refine_rules, refine_values and set_values
 * @param profile XCCDF Benchmark Profile to get all elements
 * @memberof xccdf_value_binding
 * @return new structure of xccdf_value_binding
 */
struct xccdf_value_binding * xccdf_value_binding_new(const struct xccdf_profile * profile);

/** 
 * Destructor of Policy Model structure
 * @memberof xccdf_policy_model
 */
void xccdf_policy_model_free(struct xccdf_policy_model *);

/** 
 * Destructor of Policy structure
 * @memberof xccdf_policy
 */
void xccdf_policy_free(struct xccdf_policy *);

/** 
 * Destructor of Value binding structure
 * @memberof xccdf_value_binding
 */
void xccdf_value_binding_free(struct xccdf_value_binding *);

/**
 * Import/Export function
 * Not yet implemented
 * @memberof xccdf_policy
 */
void xccdf_policy_export_variables(struct xccdf_policy *, char *export_namespace, struct oscap_export_target *);
/**
 * Import/Export function
 * Not yet implemented 
 * @memberof xccdf_policy
 */
void xccdf_policy_export_controls (struct xccdf_policy *, char *export_namespace, struct oscap_export_target *);
/**
 * Import/Export function
 * Not yet implemented
 * @memberof xccdf_policy
 */
void xccdf_policy_import_results(struct xccdf_policy *, char *import_namespace, struct oscap_import_source *);
/**
 * Import/Export function
 * Not yet implemented
 * @memberof xccdf_policy
 */
void xccdf_policy_export_results(struct xccdf_policy *, char *scoring_model_namespace, struct oscap_export_target *);

/**
 * Function to register callback for checking system
 * @param model XCCDF Policy Model
 * @param sys String representing given checking system
 * @param func Callback - pointer to function called by XCCDF Policy system when rule parsed
 * @param usr optional parameter for passing user data to callback
 * @memberof xccdf_policy_model
 * @return true if callback registered succesfully, false otherwise
 */
bool xccdf_policy_model_register_callback(struct xccdf_policy_model * model, char * sys, void * func, void * usr);

/************************************************************/
/**
 * @name Getters
 * Return value is pointer to structure's member. Do not free unless you null the pointer in the structure. 
 * Use remove function otherwise.
 * @{
 * */

/**
 * Get model from Policy (parent structure of Policy to access the benchmark)
 * @param policy XCCDF Policy
 * @return Policy model
 * @memberof xccdf_policy
 */
struct xccdf_policy_model * xccdf_policy_get_model(const struct xccdf_policy * policy);

/**
 * Get Benchmark from Policy Model
 * @param item Policy model structure
 * @return XCCDF Benchmark for given policy model
 * @memberof xccdf_policy_model
 */
struct xccdf_benchmark * xccdf_policy_model_get_benchmark(const struct xccdf_policy_model * item);

/**
 * Get Value Bindings from XCCDF Policy
 * @memberof xccdf_policy
 */
struct xccdf_value_binding  * xccdf_policy_get_values(const struct xccdf_policy * item);

/**
 * Get policies from Policy Model
 * @param model Policy Model
 * @return Iterator for list of policies
 * @memberof xccdf_policy_model
 */
struct xccdf_policy_iterator * xccdf_policy_model_get_policies(const struct xccdf_policy_model *model);

/**
 * Get selected rules from policy
 * @memberof xccdf_policy
 * @return Pointer to select iterator.
 * @retval NULL on faliure
 */
struct xccdf_select_iterator * xccdf_policy_get_selected_rules(struct xccdf_policy *);

/**
 * Get XCCDF Profile from Policy
 * @memberof xccdf_policy
 * @return XCCDF Profile
 */
struct xccdf_profile * xccdf_policy_get_profile(const struct xccdf_policy *);

/**
 * Get rules from Policy
 * @memberof xccdf_policy
 * @return xccdf_select_iterator
 */
struct xccdf_select_iterator * xccdf_policy_get_rules(const struct xccdf_policy *);

/**
 * Get refine rules from value bindings
 * @memberof xccdf_value_binding
 * @return xccdf_refine_rule_iterator
 */
struct xccdf_refine_rule_iterator * xccdf_value_binding_get_refine_rules(const struct xccdf_value_binding *);

/**
 * Get refine values from value bindings
 * @memberof xccdf_value_binding
 * @return xccdf_refine_value_iterator
 */
struct xccdf_refine_value_iterator * xccdf_value_binding_get_refine_values(const struct xccdf_value_binding *);

/**
 * Get set values from value bindings
 * @memberof xccdf_value_binding
 * @return xccdf_setvalue_iterator
 */
struct xccdf_setvalue_iterator * xccdf_value_binding_get_setvalues(const struct xccdf_value_binding *);

/**
 * Get results of all XCCDF Policy results
 * @memberof xccdf_policy_model
 */
struct xccdf_result_iterator * xccdf_policy_model_get_results(const struct xccdf_policy_model * model);

/**
 * Get XCCDF Result structure by it's idetificator if there is one
 * @memberof xccdf_policy_model
 * @return structure xccdf_result if found, NULL otherwise
 */
struct xccdf_result * xccdf_policy_model_get_result_by_id(struct xccdf_policy_model * model, const char * id);

/************************************************************
 * @} End of Getters group */

/************************************************************/
/**
 * @name Setters
 * For lists use add functions. Parameters of set functions are duplicated in memory and need to 
 * be freed by caller.
 * @{
 */

/**
 * Add Policy to Policy Model
 * @memberof xccdf_policy_model
 * @return true if policy has been added succesfully
 */
bool xccdf_policy_model_add_policy(struct xccdf_policy_model *, struct xccdf_policy *);

/**
 * Add rule to Policy
 * @memberof xccdf_policy
 * @return true if rule has been added succesfully
 */
bool xccdf_policy_add_rule(struct xccdf_policy *, struct xccdf_select *);

/**
 * Add refine rule to the Value Binding structure
 * @memberof xccdf_value_binding
 * @return true if rule has been added succesfully
 */
bool xccdf_value_binding_add_refine_rule(struct xccdf_value_binding *, struct xccdf_refine_rule *);

/**
 * Add refine value to the Value Binding structure
 * @memberof xccdf_value_binding
 * @return true if rule has been added succesfully
 */
bool xccdf_value_binding_add_refine_value(struct xccdf_value_binding *, struct xccdf_refine_value *);

/**
 * Add value to the Value Binding structure
 * @memberof xccdf_value_binding
 * @return true if rule has been added succesfully
 */
bool xccdf_value_binding_add_setvalue(struct xccdf_value_binding *, struct xccdf_setvalue *);

/**
 * Set a new selector to the Policy structure
 * @memberof xccdf_policy
 * @return true if rule has been added succesfully
 */
bool xccdf_policy_set_selected(struct xccdf_policy * policy, char * idref);

/**
 * Add result to XCCDF Policy Model
 * @memberof xccdf_policy_model
 */
bool xccdf_policy_model_add_result(struct xccdf_policy_model * model, struct xccdf_result * item);

/************************************************************
 ** @} End of Setters group */

/************************************************************/
/**
 * @name Evaluators
 * @{
 * */

/**
 * Call the checking engine for each selected rule in given policy structure
 * @param policy given Policy to evaluate
 * @memberof xccdf_policy
 * @return true if evaluation pass or false in case of error
 */
bool xccdf_policy_evaluate(struct xccdf_policy * policy);

/************************************************************
 ** @} End of Iterators group */

/************************************************************/
/**
 * @name Iterators
 * @{
 * */

/**
 * Return true if the list is not empty, false otherwise
 * @memberof xccdf_policy_iterator
 */
bool xccdf_policy_iterator_has_more(struct xccdf_policy_iterator *it);

/**
 * Return the next xccdf_policy structure from the list and increment the iterator
 * @memberof xccdf_policy_iterator
 */
struct xccdf_policy * xccdf_policy_iterator_next(struct xccdf_policy_iterator *it);

/**
 * Free the iterator structure (it makes no changes to the list structure)
 * @memberof xccdf_policy_iterator
 */
void xccdf_policy_iterator_free(struct xccdf_policy_iterator *it);

/************************************************************
 ** @} End of Iterators group */

/*
 * @}
 */
#endif


