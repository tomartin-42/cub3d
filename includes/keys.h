/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 09:21:13 by tomartin          #+#    #+#             */
/*   Updated: 2021/12/26 18:25:07 by tomartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__
#  define FORWARD	13
#  define BACK		1
#  define RIGHT		2
#  define LEFT		0
#  define ROTATE_L	123	
#  define ROTATE_R	124
# elif defined __unix__
#  define FORWARD	119
#  define BACK		115
#  define RIGHT		100
#  define LEFT		97
#  define ROTATE_L	65361
#  define ROTATE_R	65363
# endif
#endif
