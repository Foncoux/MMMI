//////////// THIS FILE MUST BE CREATED BY EXECUTING WriteAttributeDefinitionFile ////////////
//////////// DO NOT MODIFY THIS FILE MANUALLY ///////////////////////////////////////////////

#ifndef __NOMAD_4_3_RUNATTRIBUTESDEFINITIONPSDSSD__
#define __NOMAD_4_3_RUNATTRIBUTESDEFINITIONPSDSSD__

_definition = {
{ "PSD_MADS_OPTIMIZATION",  "bool",  "0",  " PSD-MADS optimization algorithm ",  " \n  \n . Use PSD-MADS algorithm. \n  \n . Argument: bool \n  \n . Description: Parallel Space Decomposition with Mads (no parallelism) \n  \n . This option deactivates any other optimization strategy. \n  \n . Example: PSD_MADS_OPTIMIZATION true \n  \n . Default: 0\n\n",  "  advanced psd mads parallel decomposition  "  , "true" , "false" , "true" },
{ "PSD_MADS_NB_VAR_IN_SUBPROBLEM",  "size_t",  "2",  " Number of variables in PSD-MADS subproblems ",  " \n  \n . When using Parallel Space Decomposition (PSD) MADS algorithm, select the \n   number of variables in Mads subproblems. \n  \n . Argument: a positive integer < INF. \n  \n . Description: Size of subproblems in PSD-Mads. \n  \n . This attribute is used only when PSD-Mads optimization is active. \n  \n . Example: PSD_MADS_NB_VAR_IN_SUBPROBLEM 3 \n  \n . Default: 2\n\n",  "  advanced psd mads parallel decomposition subproblem  "  , "true" , "false" , "true" },
{ "PSD_MADS_NB_SUBPROBLEM",  "size_t",  "INF",  " Number of PSD-MADS subproblems ",  " \n  \n . When using Parallel Space Decomposition (PSD) MADS algorithm, select the number of \n   Mads subproblems. By default (INF), the number of subproblems is adjusted to \n   cover all variables. \n  \n . Argument: a positive integer. \n  \n . This attribute is used only when PSD-Mads optimization is active. \n  \n . Example: PSD_MADS_NB_SUBPROBLEM 2 \n  \n . Default: INF\n\n",  "  advanced psd mads parallel decomposition subproblem  "  , "true" , "false" , "true" },
{ "PSD_MADS_ITER_OPPORTUNISTIC",  "bool",  "true",  " Opportunistic strategy between the Mads subproblems in PSD-MADS ",  " \n  \n . When using Parallel Space Decomposition (PSD) MADS algorithm, the launch \n   of Mads subproblems during an iteration can be opportunistically stopped when \n   a success is obtained by a Mads subproblem. \n  \n . Argument: bool \n  \n . This attribute is used only when PSD-Mads optimization is active. \n  \n . Example: PSD_MADS_OPPORTUNISTIC false \n  \n . Default: true\n\n",  "  advanced parallel space mads parallel decomposition subproblem opportunistic  "  , "true" , "false" , "true" },
{ "PSD_MADS_ORIGINAL",  "bool",  "false",  " Use NOMAD 3 strategy for mesh update in PSD-MADS ",  " \n  \n . When using Parallel Space Decomposition (PSD) MADS algorithm, \n   NOMAD 3 strategy is to always update the mesh whenever a new pollster is launched. \n   NOMAD 4 strategy is more defined as for which conditions must be met for \n   the mesh to be updated. \n  \n . Argument: bool \n  \n . This attribute is used only when PSD-Mads optimization is active. \n  \n . Example: PSD_MADS_ORIGINAL false \n  \n . Default: false\n\n",  "  advanced parallel space mads parallel decomposition subproblem original  "  , "true" , "false" , "true" },
{ "PSD_MADS_SUBPROBLEM_PERCENT_COVERAGE",  "NOMAD::Double",  "70",  " Percentage of variables that must be covered in subproblems before updating mesh ",  " \n  \n . When using Parallel Space Decomposition (PSD) MADS algorithm, \n   update (enlarge or refine) the mesh when this percentage of variables is \n   covered by subproblems. \n  \n . A lower value makes for more frequent updates. A larger value makes \n   mesh updates less frequent. \n  \n . Argument: Double between 0 and 100 \n  \n . This attribute is used only when PSD-Mads optimization is active. \n  \n . Example: PSD_MADS_SUBPROBLEM_PERCENT_COVERAGE 80 \n  \n . Default: 70\n\n",  "  advanced parallel space mads parallel subproblem  "  , "true" , "false" , "true" },
{ "SSD_MADS_OPTIMIZATION",  "bool",  "0",  " SSD-MADS optimization algorithm ",  " \n  \n . Use SSD-MADS algorithm. \n  \n . Argument: bool \n  \n . Description: Sequential Space Decomposition with Mads (no parallelism) \n  \n . This option deactivates any other optimization strategy. \n  \n . Example: SSD_MADS_OPTIMIZATION true \n  \n . Default: 0\n\n",  "  advanced ssd mads sequential decomposition  "  , "true" , "false" , "true" },
{ "SSD_MADS_NB_VAR_IN_SUBPROBLEM",  "size_t",  "2",  " Number of variables in SSD-MADS subproblems ",  " \n  \n . When using Sequential Space Decomposition (SSD) MADS algorithm, select the \n   number of variables in Mads subproblems. \n  \n . Argument: a positive integer < INF. \n  \n . Description: Size of subproblems in SSD-Mads. \n  \n . This attribute is used only when SSD-Mads optimization is active. \n  \n . Example: SSD_MADS_NB_VAR_IN_SUBPROBLEM 3 \n  \n . Default: 2\n\n",  "  advanced ssd mads sequential decomposition subproblem  "  , "true" , "false" , "true" },
{ "SSD_MADS_NB_SUBPROBLEM",  "size_t",  "INF",  " Number of SSD-MADS subproblems ",  " \n  \n . When using Sequential Space Decomposition (SSD) MADS algorithm, select the number of \n   Mads subproblems. By default (INF), the number of subproblems is adjusted to \n   cover all variables. \n  \n . Argument: a positive integer.  \n  \n . This attribute is used only when SSD-Mads optimization is active. \n  \n . Example: SSD_MADS_NB_SUBPROBLEM 2 \n  \n . Default: INF\n\n",  "  advanced ssd mads sequential decomposition subproblem  "  , "true" , "false" , "true" },
{ "SSD_MADS_RESET_VAR_PICKUP_SUBPROBLEM",  "bool",  "false",  " Reset random variable pick-up for each subproblem ",  " \n  \n . Argument: bool \n  \n . This attribute is used only when SSD-Mads optimization is active. \n  \n . Example: SSD_MADS_RESET_VAR_PICKUP_SUBPROBLEM true \n  \n . Default: false\n\n",  "  advanced ssd mads sequential decomposition subproblem  "  , "true" , "false" , "true" },
{ "SSD_MADS_ITER_OPPORTUNISTIC",  "bool",  "true",  " Opportunistic strategy between the Mads subproblems in SSD-MADS ",  " \n  \n . When using Sequential Space Decomposition (SSD) MADS algorithm, the sequence \n   of Mads subproblems during an iteration can be opportunistically stopped when \n   a success is obtained by a Mads subproblem. \n  \n . Argument: bool \n  \n . This attribute is used only when SSD-Mads optimization is active. \n  \n . Example: SSD_MADS_OPPORTUNISTIC false \n  \n . Default: true\n\n",  "  advanced sequential space ssd mads decomposition subproblem opportunistic  "  , "true" , "false" , "true" } };

#endif
