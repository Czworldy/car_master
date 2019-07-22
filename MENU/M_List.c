/* Includes ------------------------------------------------------------------*/
#include "M_List.h"
#include "M_Func.h"
#include "M_Sys.h"
#include "M_Route.h"
#include "M_Process.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/*菜单*/
struct M_Type MainMenu[M_NUM];
struct M_Type M_System[M_NUM];
struct M_Type M_Route[M_NUM];
struct M_Type M_Process[M_NUM];
struct M_Type *CurrentMenu = MainMenu;//初始化当前菜单为主菜单

struct M_Type MainMenu[M_NUM]=
{	/*Name              菜单属性                函数                节点*/
	{"1.System",        M_SMenu,                NULL,               {MainMenu, M_System} },
	{"2.Route",         M_SMenu,                NULL,               {MainMenu, M_Route} },
	{"3.Process",       M_SMenu,                NULL,               {MainMenu, M_Process} },
	{"version 2.0", 	M_Empty,        		NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
};

struct M_Type M_System[M_NUM]=
{	/*Name              菜单属性                函数                节点*/
	{"1.CCD",           M_UFunc,                sys_CCD,            {MainMenu, NULL} },
	{"2.PanTilt",       M_UFunc,                sys_PanTilt,        {MainMenu, NULL} },
	{"3.Encoder",       M_UFunc,                sys_Encoder,        {MainMenu, NULL} },
	{"4.GPS",           M_UFunc,                sys_GPS,            {MainMenu, NULL} },
	{"5.Mecanum",       M_UFunc,                sys_Mecanum,        {MainMenu, NULL} },
	{"6.Servo",         M_UFunc,                sys_Servo,          {MainMenu, NULL} },
	{"7.QR Code",       M_UFunc,                sys_QR_Code,        {MainMenu, NULL} },
	{"8.Camera",        M_UFunc,                sys_Camera,         {MainMenu, NULL} },
};

struct M_Type M_Route[M_NUM]=
{	/*Name              菜单属性                函数                节点*/
	{"1.GoLine",        M_UFunc,                route_Line,         {MainMenu, NULL} },
	{"2.Keep",          M_UFunc,                route_Keep,         {MainMenu, NULL} },
	{"3.Handle",        M_UFunc,                route_Handle,       {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
};

struct M_Type M_Process[M_NUM]=
{	/*Name              菜单属性                函数                节点*/
	{"1.Test",          M_UFunc,                process_Test,       {MainMenu, NULL} },
	{"2.All",           M_UFunc,                process_All,        {MainMenu, NULL} },
	{"3.Auto_RGB",      M_UFunc,                process_Auto_RGB,   {MainMenu, NULL} },
	{"4.CCD_Auto_RGB",  M_UFunc,                process_CCD_Auto_RGB,{MainMenu, NULL} },
	{"5.Point_Test",    M_UFunc,                process_Point_Test, {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
	{" ",               M_Empty,                NULL,               {MainMenu, NULL} },
};

/********************************    END OF FILE    ***************************/
