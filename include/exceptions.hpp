#pragma once
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <exception>

class ErroAoCarregarImagemPipe: public std::exception
{
  virtual const char* what() const throw()
  {
    return "ERRO: Não foi possível carregar a imagem para o pipe.";
  }
} erroCarregaPipe;

class ErroAoCarregarImagemBird: public std::exception
{
  virtual const char* what() const throw()
  {
    return "ERRO: Não foi possível carregar a imagem para o bird.";
  }
} erroCarregaBird;

#endif

