#pragma once
#include "QVTKWidget.h"
#include <boost/thread/thread.hpp>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkLegendScaleActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkAxisActor2D.h"
#include <QWidget>
class PCLFunc
{
public:
	PCLFunc(int xqvtk,int yqvtk);
	~PCLFunc();
	void initialVtkWidget(QWidget *dock);
	void ChangePCLView(int width,int height);
	/*void Chibiao(bool grid_enabled_);*/
	void SetLMArrayDisplay(float x[12000], float y[12000], int LMID[12000], int LMCount);
	void RedLMDisplay(int ExeType, int LMNO);
	void RedSetLMDisplay(int LMID);
	void SetUpGrid(int grid_size, float grid_step);
	void RotateViewTo(void);
	void setViewTo(int axis, int sign);
	void AddLaserLoPose(float *Pose);
	void AddCloudPointArray(float x[7200], float y[7200], float z[7200], float LaserPose[4], bool RSSIFlag, float RSSIData[7200], int ScanPointCount);
	void AddLandMarkArray(float *LMData, int LMCount);
	void DeleteOneSetLMDisplay(int LMID);
	void AddOneSetLMDisplay(int x, int y, int LMID);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	pcl::visualization::PCLVisualizer::Ptr viewer=NULL;
	bool FlagPointDisplay = true;  //true是点  false是线
	void PointOrPolyline(bool f_PointOrLine);
	void DeleteCurrLM();
	QVTKWidget *qvtk = NULL;
private:
	//点云数据存储
	std::string CloudId;
	int EveryLMFlag[40];
	int xQvtk,yQvtk;
};

