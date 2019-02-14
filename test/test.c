#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "../libft/libft.h"

void	ft_display_type(struct stat st)
{
	if (S_ISDIR(st.st_mode))
		printf("d");
	else if (S_ISCHR(st.st_mode))
		printf("c");
	else if (S_ISBLK(st.st_mode))
		printf("b");
	else if (S_ISLNK(st.st_mode))
		printf("l");
	else if (S_ISFIFO(st.st_mode))
		printf("p");
	else if (S_ISSOCK(st.st_mode))
		printf("s");
	else if (S_ISREG(st.st_mode))
		printf("-");
}

void	ft_display_rights(struct stat st)
{
	printf( (st.st_mode & S_IRUSR) ? "r" : "-");
	printf( (st.st_mode & S_IWUSR) ? "w" : "-");
	printf( (st.st_mode & S_IXUSR) ? "x" : "-");
	printf( (st.st_mode & S_IRGRP) ? "r" : "-");
	printf( (st.st_mode & S_IWGRP) ? "w" : "-");
	printf( (st.st_mode & S_IXGRP) ? "x" : "-");
	printf( (st.st_mode & S_IROTH) ? "r" : "-");
	printf( (st.st_mode & S_IWOTH) ? "w" : "-");
	printf( (st.st_mode & S_IXOTH) ? "x" : "-");
}

void	ft_display_usr_grp(struct stat st)
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(st.st_uid);
	grp = getgrgid(st.st_gid);
	printf(" %s", usr->pw_name);
	printf(" %s", grp->gr_name);
}

int		main(int ac, char **av)
{
	DIR				*dir;
	struct dirent	*diread;
	struct stat		st;

	if (ac >= 1)
	{
		dir = opendir(".");
		// ft_sort();
		while ((diread = readdir(dir)) != NULL)
		{
			if (diread->d_name[0] == '.')
				continue ;
			//	printf("STAT : %d\n", stat(diread->d_name, &st));
			if (stat(ft_strjoin("./", diread->d_name), &st) < 0)
				return (0);
			ft_display_type(st);
			ft_display_rights(st);
			printf(" %d",st.st_nlink);		// display link
			ft_display_usr_grp(st);
			printf(" %d", st.st_size);
			printf("\t%s", diread->d_name);	// display name
			printf("\n");
		}
		closedir(dir);
	}
	return (0);
}
