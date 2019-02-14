/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 12:50:11 by ezonda            #+#    #+#             */
/*   Updated: 2019/02/07 14:50:48 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
//#include <uuid/uuid.h>
#include <stdlib.h>
#include <time.h>

int		get_size(const char *name)
{
	struct stat st;

	if (stat(name, &st) != 0)
		return (0);
	return (st.st_size);
}

int		main(int ac, char **av)
{
	DIR				*dir;
	struct dirent	*diread;
	struct stat		st;
	struct passwd	*pwd;
	struct group	*grp;
	struct tm		*time;

	if (ac >= 1)
	{
		dir = opendir(av[1]);
		while ((diread = readdir(dir)) != NULL)
		{
			if (diread->d_name[0] == '.')
				continue ;
			if (stat(diread->d_name, &st) < 0)
				return (0);
			pwd = getpwuid(st.st_uid);
			grp = getgrgid(st.st_gid);
			printf("---------------------------\n");
			printf("Nom      : \t%s\n", diread->d_name);
			printf("Type     : \t");
			if (S_ISREG(st.st_mode))
				printf("Fichier\n");
			else if (S_ISDIR(st.st_mode))
				printf("Dossier\n");
			else if (S_ISLNK(st.st_mode))
				printf("Lien\n");
			if (pwd == NULL)
				exit(EXIT_FAILURE);
			printf("User     : \t%s\n", pwd->pw_name);
			if (grp == NULL)
				exit(EXIT_FAILURE);
			printf("Group    : \t%s\n", grp->gr_name);
			printf("Taille   : \t%lld bytes\n",st.st_size);
			printf("FullTime : \t%.16s\n", ctime(&st.st_ctime));
		//	printf("Day      : %d\t\n", time->tm_wday);
			printf("Modes    : \t");
			printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
			printf( (st.st_mode & S_IRUSR) ? "r" : "-");
			printf( (st.st_mode & S_IWUSR) ? "w" : "-");
			printf( (st.st_mode & S_IXUSR) ? "x" : "-");
			printf( (st.st_mode & S_IRGRP) ? "r" : "-");
			printf( (st.st_mode & S_IWGRP) ? "w" : "-");
			printf( (st.st_mode & S_IXGRP) ? "x" : "-");
			printf( (st.st_mode & S_IROTH) ? "r" : "-");
			printf( (st.st_mode & S_IWOTH) ? "w" : "-");
			printf( (st.st_mode & S_IXOTH) ? "x" : "-");
			printf("\n\n");
		}
		closedir(dir);
	}
	return (0);
}
