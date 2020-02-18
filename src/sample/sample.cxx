#include "iostream"
#include "../lib/getopt_expd.h"

int main(int argc, char *argv[])
{
	char mesh_file[1024];
	char model_file[1024];
	char gmsh_file[1024] = "NULL";
	char vtk_file[1024] = "NULL";
	char eledata_name[1024] = "Untitled";
	bool spherical = false;

	int curr;
	while(1)
	{
		int optIndex = 0;

		static struct expd_option longOpts[] = 
		{
			{"meshtool-mesh", required_argument, NULL, 'm', "Mesh filename of the Meshtools3D model.", "<mesh-file>", true},
			{"meshtool-data", required_argument, NULL, 'd', "Model filename of the Meshtools3D model.", "<data-file>", true},
			{"gmsh-msh", required_argument, NULL, 'g', "Output name of the Gmsh file.", "<gmsh-file>", false},
			{"paraview-vtk", required_argument, NULL, 'p', "Output name of the Paraview file.", "<paraview-file>", false},

			{"gmsh-elename", required_argument, NULL, 'e', 
			"Element data name of the Gmsh file. The default is \'Untitled\'.", "<eledata-name>", false},

			{"spherical-coordinate", no_argument, NULL, 's', 
			"Coordinates in the mesh file are in spherical coordinates, i.e. longitude, latitude and radius.", 0, false},

			{"help", no_argument, NULL, 'h', "Show help information.", 0, false},
			{0, 0, 0, 0, 0, 0, 0}
		};

		curr = getopt_long_expand(argc, argv, "hsm:d:g:p:e:", longOpts, &optIndex);

		if (curr == -1) break;

		switch (curr)
		{
			case 'h': //显示帮助信息
				getopt_long_help(longOpts, "3dtools2msh", " 1.0 - Convert Meshtools3D model file to Gmsh(.msh) file and Paraview(.vtk) file. \
					This program comes with ABSOLUTELY NO WARRANTY. For more information, please contact the author at zhangyiss@icloud.com (Dr. Yi Zhang).");
				return 0;
			case 'm':
				sscanf(optarg,"%s",mesh_file);
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
	return 0;
}