/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:21:13 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/15 09:51:14 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__
# define FORWARD	13	
# define BACK		1
# define RIGHT		2
# define LEFT		0
# define ROTATE_L	123	
# define ROTATE_R	124
# elif defined __unix__
# define FORWARD	115
# define BACK		119
# define RIGHT		97
# define LEFT		100
# define ROTATE_L	65361
# define ROTATE_R	65363
# endif
#endif

