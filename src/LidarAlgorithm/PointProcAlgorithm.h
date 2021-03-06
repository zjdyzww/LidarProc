/*
 * @Descripttion: point cloud process algorithm segment method
 * @version: v1.1 add kmeans segment method
 * @Author: Frank.Wu
 * @Date: 2019-11-18 21:31:07
 * @LastEditors  : Frank.Wu
 * @LastEditTime : 2020-01-16 17:05:23
 */

#pragma once
//
// Created by Frank.Wu on 18-07-10.
//

#ifndef _POINTPROCALG_H_
#define _POINTPROCALG_H_

#include "Geometry.h"
#include "../LidarBase/LASPoint.h"
#include "../LidarBase/LASReader.h"
using namespace GeometryLas;

namespace LasAlgorithm {
	/*
		point cloud segment algorithm class
	*/
	class PointCloudSegment
	{
	public:
		/*
		using dbscan algorithm to segment point cloud
		@param pointSet:input point set
		@param type:output type of each point,from 1 to segment number
		@param knnRange:param of distance
		@return segment number
		*/
		long PointCloudSegment_DBScan(Point3Ds pointSet, int *type, float knnRange);

		/*
		according to new version of LASDataset the kdtree was built in block
		so the input data is the LASDataset,and do not need construct the
		kdtree once more
		@param lasDataset:LAS dataset
		@param type:output type of each point,from 1 to segment number(take more memory but convient)
		@param knnRange:param of distance
		@return segment number
		*/
		long PointCoudSegment_DBScan(ILASDataset *lasDataset, int **type, float knnRange);


		long PointCoudSegment_TypeExport(Point3Ds pointSet, int *type, int iType, const char* dir);
	};

	/*
	point cloud segment algorithm class with direction
	consider the direction of the point set
	*/
	class PointCloudSegmentWithDirection :public PointCloudSegment
	{
	public:
		/*
		面状点云的提取分割，对于不同的形状的点云所需要的方向特征是不一样的
		对于面状的点云特征来说重要的是法线方向
		@param pointSet 输入的点集
		@param type 点云分类类别
		@param directionRange 角度阈值
		@param knnRange KNN聚类范围阈值
		*/
		long PointCloudSegmentDirect_SegmentPoly(Point3Ds pointSet, int *type, float directionRange, float knnRange);

		void  Test();
		//
		//long PointCloudSegmentDirect_MergePartNearest(Point3Ds pointSet, int *type);

	protected:
		//
		Point3Ds PointCloudSegmentDirect_CalDirectVec(Point3Ds pointSet, int *type, int iType);

		Point3Ds PointCloudSegmentDirect_CalDirectVec(Point3Ds pointSet);
	};

	/**
	 * @name: 
	 * @msg: using kmeans method to segment the point cloud data
	 */
	class PointCloudSegmentWithKMeans:public PointCloudSegment
	{
	public:
		/**
		 * @name: 
		 * @msg: 
		 * @param {type} 
		 * @return: 
		 */
		long PointCloudSegment_KMeans(ILASDataset *lasDataset,int nType,int *type,double thresStop);

		/**
		 * @name: kmeans segment method
		 * @msg: 
		 * @param 
		 * Point3Ds pointSet: point cloud set
		 * int nType: : types
		 * int *type: type of each point
		 * double thresStop: stop iterator condition
		 * @return: 
		 */
		long PointCloudSegment_KMeans(Point3Ds pointSet,int nType,int *type,double thresStop);

	protected:
		/**
		 * @name: kmeans segment iteration process
		 * @msg: 
		 * @param 
		 * Point3Ds pointSet: point cloud set
		 * int nType: types
		 * Point3Ds clusterCenter: cluster center point
		 * int *type: type of each point
		 * @return: error code
		 */
		long PointCloudSegment_KMeansIterator(Point3Ds pointSet,int nType,Point3Ds &clusterCenter,int *type);
	};

#endif // !_POINTPROCALG_H_

}


