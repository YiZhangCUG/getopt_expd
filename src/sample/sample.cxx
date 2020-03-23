#include "iostream"
#include "../lib/getopt_expd.h"

int main(int argc, char *argv[])
{
	char mesh_file[1024] = "NULL";
	char model_file[1024] = "NULL";
	char gmsh_file[1024] = "NULL";
	char vtk_file[1024] = "NULL";
	char eledata_name[1024] = "Untitled";
	bool spherical = false;

	static struct expd_option longOpts_Expd[] = 
	{
		{"Mesh filename of the Meshtools3D model.", "<mesh-file>", true},
		{"Model filename of the Meshtools3D model.", "<data-file>", true},
		{"Output name of the Gmsh file.", "<gmsh-file>", false},
		{"Output name of the Paraview file.", "<paraview-file>", false},
		{"Element data name of the Gmsh file. The default is \'Untitled\'.", "<eledata-name>", false},
		{"Coordinates in the mesh file are in spherical coordinates, i.e. longitude, latitude and radius.", 0, false},
		{"Show help information.", 0, false},
		{0, 0, 0}
	};

	//static option *longOpts = NULL;
	//longOpts = getopt_get_options(longOpts_Expd);
	static struct option longOpts[] = 
	{
		{"meshtool-mesh", required_argument, NULL, 'm'},
		{"meshtool-data", required_argument, NULL, 'd'},
		{"gmsh-msh", required_argument, NULL, 'g'},
		{"paraview-vtk", required_argument, NULL, 'p'},
		{"gmsh-elename", required_argument, NULL, 'e'},
		{"spherical-coordinate", no_argument, NULL, 's'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};

	int curr;
	while(1)
	{
		int optIndex = 0;

		curr = getopt_long(argc, argv, "hsm:d:g:p:e:", longOpts, &optIndex);

		if (curr == -1) break;

		switch (curr)
		{
			case 'h': //显示帮助信息
				getopt_long_help(longOpts, longOpts_Expd, "3dtools2msh", " 1.0 - Convert Meshtools3D model file to Gmsh(.msh) file and Paraview(.vtk) file. \
					This program comes with ABSOLUTELY NO WARRANTY. For more information, please contact the author at zhangyiss@icloud.com (Dr. Yi Zhang).");
				return 0;
			case 'm':
				sscanf(optarg,"%s",mesh_file);
				if (!strcmp(mesh_file, "NULL"))
					getopt_long_option_info('m', longOpts, longOpts_Expd);
				break;
			case 'd':
				sscanf(optarg,"%s",model_file);
				break;
			case 'g':
				sscanf(optarg,"%s",gmsh_file);
			case 'p':
				sscanf(optarg,"%s",vtk_file);
				break;
			case 'e':
				sscanf(optarg,"%s",eledata_name);
				break;
			case 's':
				spherical = true;
				break;
			case '?':
				getopt_long_help(longOpts, longOpts_Expd, "3dtools2msh", " - Unknown options. Please see the help information below.");
				break;
			default:
				abort();
		}
	}

	std::cout
	<< mesh_file << std::endl
	<< model_file << std::endl
	<< gmsh_file << std::endl
	<< vtk_file << std::endl
	<< eledata_name << std::endl
	<< spherical << std::endl;

	//if (longOpts != NULL) delete[] longOpts;
	return 0;
}