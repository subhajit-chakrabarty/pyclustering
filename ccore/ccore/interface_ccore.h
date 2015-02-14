/**************************************************************************************************************

Interface of the CCORE library that is used by pyclustering.

Based on article description:
 - S.Guha, R.Rastogi, K.Shim. CURE: An Efficient Clustering Algorithm for Large Databases. 1998.

Copyright (C) 2015    Andrei Novikov (spb.andr@yandex.ru)

pyclustering is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pyclustering is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

**************************************************************************************************************/

#ifndef _INTERFACE_CCORE_H_
#define _INTERFACE_CCORE_H_

#if defined (__GNUC__) && defined(__unix__)
	#define DECLARATION __attribute__ ((__visibility__("default")))
#elif defined (WIN32)
	#define DECLARATION __declspec(dllexport)
#else
	#error Unsupported platform
#endif

typedef enum pyclustering_type_data {
	PYCLUSTERING_TYPE_INT				= 0,
	PYCLUSTERING_TYPE_UNSIGNED_INT		= 1,
	PYCLUSTERING_TYPE_FLOAT				= 2,
	PYCLUSTERING_TYPE_DOUBLE			= 3,
	PYCLUSTERING_TYPE_LONG				= 4,
	PYCLUSTERING_TYPE_UNSIGNED_LONG		= 5,
	PYCLUSTERING_TYPE_LIST				= 6
} pyclustering_type_data;

typedef struct pyclustering_package {
	unsigned int size;
	unsigned int type;		/* pyclustering_type_data    */
	void * data;			/* pointer to data           */

	pyclustering_package(void) { }
	pyclustering_package(unsigned int package_type) : type(package_type) { }
} pyclustering_package;

typedef struct cluster_representation {
	unsigned int			size;
	unsigned int			* objects;
} cluster_representation;

typedef struct clustering_result {
	unsigned int			size;
	cluster_representation	* clusters;
} clustering_result;

typedef struct data_representation {
	unsigned int			size;
	unsigned int			dimension;
	double					** objects;
} data_representation;

typedef struct dynamic_result {
	unsigned int			size_dynamic;
	unsigned int			size_network;
	double					* times;
	double					** dynamic;
} dynamic_result;

/***********************************************************************************************
 *
 * @brief   Free clustering results that have been provided by CCORE to client.
 *
 * @param   (in) pointer            - pointer to clustering results.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void free_clustering_result(clustering_result * pointer);

/***********************************************************************************************
 *
 * @brief   Free dynamic that have been provided by CCORE to client.
 *
 * @param   (in) pointer            - pointer to dynamic.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void free_dynamic_result(dynamic_result * pointer);

extern "C" DECLARATION void free_pyclustering_package(pyclustering_package * package);

/***********************************************************************************************
 *
 * @brief   Clustering algorithm DBSCAN returns allocated clusters and noise that are consisted
 *          from input data.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) radius				- connectivity radius between points, points may be connected
 *                                    if distance between them less then the radius.
 *          (in) minumum_neighbors	- minimum number of shared neighbors that is required for
 *                                    establish links between points.
 *
 * @return	Returns result of clustering - array of allocated clusters. The last cluster in the
 * 			array is noise.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * dbscan_algorithm(const data_representation * const sample, const double radius, const unsigned int minumum_neighbors);

/***********************************************************************************************
 *
 * @brief   Clustering algorithm CURE returns allocated clusters.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) number_clusters	- number of clusters that should be allocated.
 *          (in) number_repr_points	- number of representation points for each cluster.
 *          (in) compression        - coefficient defines level of shrinking of representation 
 *                                    points toward the mean of the new created cluster after 
 *                                    merging on each step.
 *
 * @return	Returns result of clustering - array of allocated clusters.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * cure_algorithm(const data_representation * const sample, const unsigned int number_clusters, const unsigned int number_repr_points, const double compression);

/***********************************************************************************************
 *
 * @brief   Clustering hierarchical algorithm returns allocated clusters.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) number_clusters	- number of cluster that should be allocated.
 *
 * @return	Returns result of clustering - array of allocated clusters.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * hierarchical_algorithm(const data_representation * const sample, const unsigned int number_clusters);

/***********************************************************************************************
 *
 * @brief   Clustering algorithm K-Means returns allocated clusters.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) initial_centers	- initial coordinates of centers of clusters.
 *          (in) tolerance			- stop condition: if maximum value of change of centers of
 *                                    clusters is less than tolerance than algorithm will stop
 *                                    processing.
 *
 * @return	Returns result of clustering - array of allocated clusters.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * kmeans_algorithm(const data_representation * const sample, const data_representation * const initial_centers, const double tolerance);

/***********************************************************************************************
 *
 * @brief   Clustering algorithm ROCK returns allocated clusters.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) radius				- connectivity radius (similarity threshold).
 *          (in) number_clusters	- defines number of clusters that should be allocated from
 *          						  the input data set.
 *          (in) threshold			- value that defines degree of normalization that influences
 *                                    on choice of clusters for merging during processing.
 *
 * @return	Returns result of clustering - array of allocated clusters.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * rock_algorithm(const data_representation * const sample, const double radius, const unsigned int number_clusters, const double threshold);

/***********************************************************************************************
 *
 * @brief   Clustering algorithm X-Means returns allocated clusters.
 *
 * @param   (in) sample				- input data for clustering.
 *          (in) initial_centers	- initial coordinates of centers of clusters.
 *          (in) kmax               - maximum number of clusters that can be allocated.
 *          (in) tolerance			- stop condition for local parameter improvement.
 *
 * @return	Returns result of clustering - array of allocated clusters.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * xmeans_algorithm(const data_representation * const sample, const data_representation * const initial_centers, const unsigned int kmax, const double tolerance);

/***********************************************************************************************
 *
 * @brief   Create oscillatory network Sync that is based on Kuramoto model.
 *
 * @param   (in) size				- number of oscillators in the network.
 *          (in) weight_factor		- coupling strength of the links between oscillators.
 *          (in) frequency_factor	- multiplier of internal frequency of the oscillators.
 *          (in) connection_type	- type of connection between oscillators in the network.
 *          (in) initial_phases		- type of initialization of initial phases of oscillators.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void * create_sync_network(const unsigned int size, const double weight_factor, const double frequency_factor, const unsigned int connection_type, const unsigned int initial_phases);

/***********************************************************************************************
 *
 * @brief   Destroy sync_network (calls destructor).
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void destroy_sync_network(const void * pointer_network);

/***********************************************************************************************
 *
 * @brief   Simulate dynamic of the oscillatory Sync network.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *          (in) steps				- number steps of simulations during simulation.
 *          (in) time				- time of simulation.
 *          (in) solver				- type of solution (solving).
 *          (in) collect_dynamic	- true - returns whole dynamic of oscillatory network, 
 *                                    otherwise returns only last values of dynamics.
 *
 * @return	Returns dynamic of simulation of the network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION dynamic_result * simulate_sync_network(const void * pointer_network, unsigned int steps, const double time, const unsigned int solver, const bool collect_dynamic);

/***********************************************************************************************
 *
 * @brief   Simulate dynamic of the oscillatory Sync network until stop condition is not reached.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *          (in) order				- order of process synchronization, destributed 0..1.
 *          (in) solver				- type of solution (solving).
 *          (in) collect_dynamic	- if true - returns whole dynamic of oscillatory network, 
 *                                    otherwise returns only last values of dynamics.
 *          (in) step				- time step of one iteration of simulation.
 *          (in) step_int			- integration step, should be less than step.
 *          (in) threshold_changes	- additional stop condition that helps prevent infinite 
 *                                    simulation, defines limit of changes of oscillators between 
 *                                    current and previous steps.
 *
 * @return	Returns dynamic of simulation of the network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION dynamic_result * simulate_dynamic_sync_network(const void * pointer_network, const double order, const unsigned int solver, const bool collect_dynamic, const double step, const double step_int, const double threshold_changes);

/***********************************************************************************************
 *
 * @brief   Allocate clusters of ensembles of synchronous oscillators where each
 *          synchronous ensemble corresponds to only one cluster for Sync network.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *          (in) tolerance			- maximum error for allocation of synchronous ensemble 
 *                                    oscillators.
 *
 * @return	Returns ensembles of synchronous oscillators as clustering result.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * allocate_sync_ensembles_sync_network(const void * pointer_network, const double tolerance);

/***********************************************************************************************
 *
 * @brief   Returns level of global synchorization in the network.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *
 * @return	Returns level of global synchorization in the network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION double sync_order(const void * pointer_network);

/***********************************************************************************************
 *
 * @brief   Returns level of local (partial) synchronization in the network.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *
 * @return	Returns level of global synchorization in the network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION double sync_local_order(const void * pointer_network);

/***********************************************************************************************
 *
 * @brief   Create oscillatory network SYNC for cluster analysis.
 *
 * @param   (in) sample                - input data for clustering.
 * @param   (in) connectivity_radius   - connectivity radius between points.
 * @param   (in) enable_conn_weight    - if True - enable mode when strength between oscillators 
 *                                       depends on distance between two oscillators. Otherwise
 *                                       all connection between oscillators have the same strength.
 * @param   (in) initial_phases        - type of initialization of initial phases of oscillators.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void * create_syncnet_network(const data_representation * const sample, const double connectivity_radius, const bool enable_conn_weight, const unsigned int initial_phases);

/***********************************************************************************************
 *
 * @brief   Destroy SyncNet (calls destructor).
 *
 * @param   (in) pointer_network       - pointer to the SyncNet network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void destroy_syncnet_network(const void * pointer_network);

/***********************************************************************************************
 *
 * @brief   Simulate oscillatory network SYNC until clustering problem is not resolved.
 *
 * @param   (in) order             - order of synchronization that is used as indication for 
 *                                   stopping processing.
 * @param   (in) solver            - specified type of solving diff. equation. 
 * @param   (in) collect_dynamic   - specified requirement to collect whole dynamic of the network.
 *
 * @return  Return last values of simulation time and phases of oscillators as a tuple if 
 *          collect_dynamic is False, and whole dynamic if collect_dynamic is True.
 *
 ***********************************************************************************************/
extern "C" DECLARATION dynamic_result * process_syncnet(const void * pointer_network, const double order, const unsigned int solver, const bool collect_dynamic);

/***********************************************************************************************
 *
 * @brief   Allocate clusters of ensembles of synchronous oscillators where each
 *          synchronous ensemble corresponds to only one cluster for SYNC network.
 *
 * @param   (in) pointer_network	- pointer to the Sync network.
 *          (in) tolerance			- maximum error for allocation of synchronous ensemble 
 *                                    oscillators.
 *
 * @return	Returns ensembles of synchronous oscillators as clustering result.
 *
 ***********************************************************************************************/
extern "C" DECLARATION clustering_result * get_clusters_syncnet(const void * pointer_network, const double tolerance);

/***********************************************************************************************
 *
 * @brief   Create oscillatory network hierarchical HSyncNet for cluster analysis.
 *
 * @param   (in) sample                - input data for clustering.
 * @param   (in) number_clusters       - number of clusters that should be allocated.
 * @param   (in) initial_phases        - type of initialization of initial phases of oscillators.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void * create_hsyncnet(const data_representation * const sample, const unsigned int number_clusters, const unsigned int initial_phases);

/***********************************************************************************************
 *
 * @brief   Destroy oscillatory network HSyncNet (calls destructor).
 *
 * @param   (in) pointer_network      - pointer to HSyncNet oscillatory network.
 *
 ***********************************************************************************************/
extern "C" DECLARATION void destroy_hsyncnet_network(const void * pointer_network);

/***********************************************************************************************
 *
 * @brief   Simulate oscillatory network hierarchical SYNC until clustering problem is not resolved.
 *
 * @param   (in) order             - order of synchronization that is used as indication for 
 *                                   stopping processing.
 * @param   (in) solver            - specified type of solving diff. equation. 
 * @param   (in) collect_dynamic   - specified requirement to collect whole dynamic of the network.
 *
 * @return  Return last values of simulation time and phases of oscillators as a tuple if 
 *          collect_dynamic is False, and whole dynamic if collect_dynamic is True.
 *
 ***********************************************************************************************/
extern "C" DECLARATION dynamic_result * process_hsyncnet(const void * pointer_network, const double order, const unsigned int solver, const bool collect_dynamic);


extern "C" DECLARATION void * som_create(const data_representation * const sample, const unsigned int num_rows, const unsigned int num_cols, const unsigned int num_epochs, const unsigned int type_conn, const unsigned int type_init);

extern "C" DECLARATION void som_destroy(const void * pointer);

extern "C" DECLARATION unsigned int som_train(const void * pointer, const bool autostop);

extern "C" DECLARATION unsigned int som_simulate(const void * pointer, const data_representation * const pattern);

extern "C" DECLARATION unsigned int som_get_winner_number(const void * pointer);

extern "C" DECLARATION unsigned int som_get_size(const void * pointer);

extern "C" DECLARATION pyclustering_package * som_get_weights(const void * pointer);

extern "C" DECLARATION pyclustering_package * som_get_capture_objects(const void * pointer);

extern "C" DECLARATION pyclustering_package * som_get_awards(const void * pointer);

extern "C" DECLARATION pyclustering_package * som_get_neighbors(const void * pointer);

#endif
